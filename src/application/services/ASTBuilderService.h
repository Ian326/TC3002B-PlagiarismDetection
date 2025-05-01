#ifndef ASTBUILDERSERVICE_H
#define ASTBUILDERSERVICE_H

#include <fstream>
#include <utility> 
#include <vector>
#include <stack>
#include <string>
#include <cstdio>
#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../../domain/services/CommandExecutor.h"
#include "../../domain/services/StringService.h"


/**
 * @class ASTBuilderService
 * @brief This class builds an AST for the given code.
 */
class ASTBuilderService {
    private:
        const static std::filesystem::path PARSER;
        const static std::filesystem::path C; 
        const static std::filesystem::path JAVA;
        const static std::filesystem::path TEMP_DIR;

        void buildTree(std::vector<std::pair<std::string,int>>&, AbstractSyntaxTree*);

    public:
        ASTBuilderService();
        ~ASTBuilderService();
        AbstractSyntaxTree* build(std::filesystem::path&);
};


/**
 * @brief Constructor for the ASTBuilderService class.
 */
ASTBuilderService::ASTBuilderService(){}


/**
 * @brief Destructor for the ASTBuilderService class.
 */
ASTBuilderService::~ASTBuilderService(){}



/**
 * @brief Call tree-sitter to generate AST.
 * @param srcCode code to parse
 * @return Abstract Syntax Tree (AST)
 */
AbstractSyntaxTree* ASTBuilderService::build(std::filesystem::path &sourceCode) {
    std::string language = sourceCode.extension().string() == "java" ? "java" : "cpp";
    std::string grammar = language == "java" ? JAVA.string() : C.string();
    std::filesystem::path outputLocation = TEMP_DIR / "output.txt";
    
    // python3 parser.py lang_grammar path_grammar file
    std::string command = "python3 " + PARSER.string() + " " + language + " " + grammar + " " + sourceCode.string();
    std::string deconstructedTreeFile = CommandExecutor::execute(command);

    std::vector<std::pair<std::string,int>> preOrderList;
    std::vector<std::string> splitted;
    std::string nextLine;
    std::ifstream input;

    // Open output file created by python
    input.open(outputLocation.c_str(), std::ios::in);

    if (input.fail()) {
        std::cout << "El archivo no se pudo abrir" << std::endl;
        return nullptr;
    }

    while (std::getline(input, nextLine) && nextLine != "EOF"){
        splitted = StringService::split(nextLine, ' ');
        preOrderList.push_back(std::make_pair(splitted[0], stoi(splitted[1])));
    }

    input.close();
    
    if (!preOrderList.size()) {
        return nullptr;
    }
    
    if (preOrderList.size() == 1) {
        return new AbstractSyntaxTree(new TreeNode(preOrderList[0].first));
    }
  
    TreeNode* root = new TreeNode(preOrderList[0].first);
  
    AbstractSyntaxTree* tree = new AbstractSyntaxTree(root);

    buildTree(preOrderList, tree);

    return tree;
}


/**
 * @brief Reconstruct AST from preorder list
 * @param preOrderList list of pairs with node tag and level
 * @param tree AST where nodes will be added
 */
void ASTBuilderService::buildTree(std::vector<std::pair<std::string,int>>& preOrderList, AbstractSyntaxTree* tree){
    std::stack<std::pair<TreeNode*, int>> parents;

    parents.push(std::make_pair(tree->getRoot(), preOrderList[0].second));
    
    for (int i = 1; i < preOrderList.size(); i++) {
        TreeNode* node = new TreeNode(preOrderList[i].first);
        int level = preOrderList[i].second;

        while (!parents.empty() && parents.top().second >= level) {
            parents.pop();
        }
        
        tree->addChild(parents.top().first, node);
        parents.push(std::make_pair(node, preOrderList[i].second));
    }
}

const std::filesystem::path ASTBuilderService::PARSER = "tools/AST.py";
const std::filesystem::path ASTBuilderService::C = "./domain/entities/grammars/cpp.so";
const std::filesystem::path ASTBuilderService::JAVA = "./domain/entities/grammars/java.so";
const std::filesystem::path ASTBuilderService::TEMP_DIR = std::filesystem::temp_directory_path();

#endif // ASTBUILDERSERVICE_H