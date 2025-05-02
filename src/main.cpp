#include <bits/stdc++.h>

#include "./application/controllers/ASTBuilderController.h"
#include "./application/controllers/CFGBuilderController.h"
#include "./application/controllers/SimilarityController.h"
#include "./domain/entities/AbstractSyntaxTree.h"
#include "./domain/entities/UGraph.h"
#include<bits/stdc++.h>

using namespace std;

int main() {
    filesystem::path basePath = "../resources/datasets/original/java";
    string first, second;

    cout << "Welcome to java similarity system" << endl;

    cout << "Enter name of first file: ";
    cin >> first;
    
    cout << "Enter name of second file: ";
    cin >> second;

    filesystem::path firstPath = basePath / first;
    filesystem::path secondPath = basePath / second;

    ASTBuilderController treeBuilderController;
    AbstractSyntaxTree* firstTree = treeBuilderController.getTree(firstPath);
    AbstractSyntaxTree* secondTree = treeBuilderController.getTree(secondPath);

    CFGBuilderController cfgBuilderController;
    UGraph<string>* firstGraph = cfgBuilderController.getGraph(firstTree);
    UGraph<string>* secondGraph = cfgBuilderController.getGraph(secondTree);

    SimilarityController similarityController;

    cout << "Calculated Similarity: " << similarityController.getSimilarity(firstGraph, secondGraph) << endl;

    return 0;
}