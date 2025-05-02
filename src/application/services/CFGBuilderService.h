#ifndef CFGBUILDERSERVICE_H
#define CFGBUILDERSERVICE_H

#include <string>
#include <stack>
#include <iterator>
#include <set>
#include "../../domain/entities/UGraph.h"
#include "../../domain/services/CommandExecutor.h"
#include "../../domain/services/StringService.h"


/**
 * @class CFGBuilderService
 * @brief This class builds an CFG from a given AST.
 */
class CFGBuilderService {
    private:
        const static std::filesystem::path PARSER;
        const static std::filesystem::path JAVA;
        const static std::filesystem::path TEMP_DIR;
    
    public:
        CFGBuilderService();
        ~CFGBuilderService();
        UGraph<std::string>* build(std::filesystem::path &);
};


/**
 * @brief Constructor for the CFGBuilderService class.
 */
CFGBuilderService::CFGBuilderService(){}


/**
 * @brief Destructor for the CFGBuilderService class.
 */
CFGBuilderService::~CFGBuilderService(){}


/**
 * @brief Construct CFG from AST
 * @param tree input AST
 * @return Resulting UGraph
 */
UGraph<std::string>* CFGBuilderService::build(std::filesystem::path &sourceCode) {
    std::map<int, std::pair<int, std::string>> vertexes;
    std::ifstream input;
    std::string nextLine;
    std::string language = "java";
    std::string grammar = JAVA.string();
    std::string command = "python3 " + PARSER.string() + " " + language + " " + grammar + " " + sourceCode.string();
    std::string graphConnections = CommandExecutor::execute(command);
    std::filesystem::path outputLocation = TEMP_DIR / "output.txt";

    UGraph<std::string>* graph = new UGraph<std::string>(true);

    // Open output file created by python
    input.open(outputLocation.c_str(), std::ios::in);

    if (input.fail()) {
        std::cout << "El archivo no se pudo abrir" << std::endl;
        return nullptr;
    }

    std::vector<std::string> aux;
    std::getline(input, nextLine); // Ignore text "Nodes in CFG 1:"

    while (std::getline(input, nextLine) && nextLine != "") {
        aux = StringService::divideInTwo(nextLine, ' ');
        vertexes[stoi(aux[0])] = std::make_pair(stoi(aux[0]), aux[1]);
    }
    
    std::getline(input, nextLine); // Ignore text Edges in CFG":"
    while (std::getline(input, nextLine) && nextLine != "\n") {
        aux = StringService::divideInTwo(nextLine, ' ');
        graph->addEdge(vertexes[stoi(aux[0])],vertexes[stoi(aux[1])]);
    }

    input.close();

    return graph;
}
const std::filesystem::path CFGBuilderService::PARSER = "tools/AST.py";
const std::filesystem::path CFGBuilderService::JAVA = "./domain/entities/grammars/java.so";
const std::filesystem::path CFGBuilderService::TEMP_DIR = std::filesystem::temp_directory_path();

#endif // CFGBUILDERSERVICE_H