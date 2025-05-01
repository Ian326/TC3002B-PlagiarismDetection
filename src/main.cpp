#include <bits/stdc++.h>
#include <iostream>

#include "./application/controllers/ASTBuilderController.h"
#include "./application/controllers/CFGBuilderController.h"
#include "./domain/entities/AbstractSyntaxTree.h"
#include "./domain/entities/UGraph.h"

using namespace std;

int main() {
    std::filesystem::path sourceCode = "../resources/datasets/original/java/HelloWorld.java";

    ASTBuilderController treeBuilderController;
    AbstractSyntaxTree* tree = treeBuilderController.getTree(sourceCode);

    CFGBuilderController cfgBuilderController;
    UGraph<string>* graph = cfgBuilderController.getGraph(tree);


    cout << "AST: \n" << tree->toString("", tree->getRoot(), 0);
    cout << "CFG: \n" << graph->toString();

    return 0;
}