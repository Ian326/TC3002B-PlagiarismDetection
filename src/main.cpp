#include <bits/stdc++.h>
#include <iostream>

#include "./application/controllers/TreeBuilderController.h"
#include "./domain/entities/AbstractSyntaxTree.h"

using namespace std;

int main(){
    std::filesystem::path original = "../resources/datasets/original/1.cpp";
    std::filesystem::path plagiarized = "../resources/datasets/plagiarized/1.cpp";

    TreeBuilderController treeBuilderController;
    AbstractSyntaxTree* ast = treeBuilderController.getTree(original, plagiarized);
    
    return 0;
}