#ifndef TREEBUILDERSERVICE_H
#define TREEBUILDERSERVICE_H

#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../../domain/services/CommandExecutor.h"


/**
 * @class TreeBuilderService
 * @brief This class builds an AST for the given code.
 */
class TreeBuilderService {
    private:
        const static std::filesystem::path PARSER;
        const static std::filesystem::path C; 
        const static std::filesystem::path JAVA;

    public:
        TreeBuilderService();
        ~TreeBuilderService();
        AbstractSyntaxTree* build(std::filesystem::path&);
};


/**
 * @brief Constructor for the TreeBuilderService class.
 */
TreeBuilderService::TreeBuilderService(){}


/**
 * @brief Destructor for the TreeBuilderService class.
 */
TreeBuilderService::~TreeBuilderService(){}



/**
 * @brief Call tree-sitter to generate AST.
 * @param srcCode code to parse
 * @return Abstract Syntax Tree (AST)
 */
AbstractSyntaxTree* TreeBuilderService::build(std::filesystem::path &sourceCode) {
    std::string language = sourceCode.extension().string() == "java" ? "java" : "cpp";
    std::string grammar = language == "java" ? JAVA.string() : C.string();
    
    // python3 parser.py lang_grammar path_grammar file
    std::string command = "python3 " + PARSER.string() + " " + language + " " + grammar + " " + sourceCode.string();
    std::string deconstructedTreeFile = CommandExecutor::execute(command);

    return nullptr;
}

const std::filesystem::path TreeBuilderService::PARSER = "tools/AST.py";
const std::filesystem::path TreeBuilderService::C = "./domain/entities/grammars/cpp.so";
const std::filesystem::path TreeBuilderService::JAVA = "./domain/entities/grammars/java.so";

#endif // TREEBUILDERSERVICE_H