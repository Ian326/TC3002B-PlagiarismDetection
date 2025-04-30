#ifndef TREEBUILDERCONTROLLER_H
#define TREEBUILDERCONTROLLER_H

#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../services/TreeBuilderService.h"


/**
 * @class TreeBuilderController
 * @brief This class calls service to build an AST for the given code.
 */
class TreeBuilderController {
    public:
        TreeBuilderController();
        ~TreeBuilderController();
        AbstractSyntaxTree* getTree(std::filesystem::path&);
};


/**
 * @brief Comstructor for the TreeBuilderController class.
 */
TreeBuilderController::TreeBuilderController() {}


/**
 * @brief Destructor for the TreeBuilderController class.
 */
TreeBuilderController::~TreeBuilderController(){}


/**
 * @brief Call TreeBuilderService to generate AST.
 * @param sourceCode code to parse
 * @return Abstract Syntax Tree (AST)
 */
AbstractSyntaxTree* TreeBuilderController::getTree(std::filesystem::path& sourceCode){
    TreeBuilderService builder;
    return builder.build(sourceCode);
}

#endif // TREEBUILDERCONTROLLER_H