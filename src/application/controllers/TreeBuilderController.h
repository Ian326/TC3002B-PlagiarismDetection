#ifndef TREEBUILDERCONTROLLER_H
#define TREEBUILDERCONTROLLER_H

#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../services/TreeBuilderService.h"

class TreeBuilderController {
    public:
        TreeBuilderController();
        ~TreeBuilderController();
        AbstractSyntaxTree* getTree(std::filesystem::path& original, std::filesystem::path& plagiarized);
};

TreeBuilderController::TreeBuilderController() {}

TreeBuilderController::~TreeBuilderController(){}

AbstractSyntaxTree* TreeBuilderController::getTree(std::filesystem::path& original, std::filesystem::path& plagiarized){
    TreeBuilderService builder;
    return builder.build(original, plagiarized);
}

#endif // TREEBUILDERCONTROLLER_H