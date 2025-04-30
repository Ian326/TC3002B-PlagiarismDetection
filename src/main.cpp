#include <bits/stdc++.h>
#include <iostream>

#include "./application/controllers/TreeBuilderController.h"
#include "./domain/entities/AbstractSyntaxTree.h"

using namespace std;

int main(){
    std::filesystem::path sourceCode = "../resources/datasets/original/1.cpp";

    TreeBuilderController treeBuilderController;
    AbstractSyntaxTree* ast = treeBuilderController.getTree(sourceCode);
    
    return 0;
}