#ifndef ASTBUILDERCONTROLLER_H
#define ASTBUILDERCONTROLLER_H

#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../services/ASTBuilderService.h"


/**
 * @class ASTBuilderController
 * @brief This class calls service to build an AST for the given code.
 */
class ASTBuilderController {
    public:
        ASTBuilderController();
        ~ASTBuilderController();
        AbstractSyntaxTree* getTree(std::filesystem::path&);
};


/**
 * @brief Comstructor for the ASTBuilderController class.
 */
ASTBuilderController::ASTBuilderController() {}


/**
 * @brief Destructor for the ASTBuilderController class.
 */
ASTBuilderController::~ASTBuilderController(){}


/**
 * @brief Call TreeBuilderService to generate AST.
 * @param sourceCode code to parse
 * @return Abstract Syntax Tree (AST)
 */
AbstractSyntaxTree* ASTBuilderController::getTree(std::filesystem::path& sourceCode){
    ASTBuilderService builder;
    return builder.build(sourceCode);
}

#endif // TREEBUILDERCONTROLLER_H