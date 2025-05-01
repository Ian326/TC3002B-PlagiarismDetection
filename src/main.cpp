#include <bits/stdc++.h>
#include <iostream>

#include "./application/controllers/ASTBuilderController.h"
#include "./domain/entities/AbstractSyntaxTree.h"

using namespace std;

int main(){
    std::filesystem::path sourceCode = "../resources/datasets/original/1.cpp";

    ASTBuilderController treeBuilderController;
    AbstractSyntaxTree* tree = treeBuilderController.getTree(sourceCode);

    // tree->print(tree->getRoot(), 0);

    return 0;
}