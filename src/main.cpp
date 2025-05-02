#include <bits/stdc++.h>

#include "./application/controllers/CFGBuilderController.h"
#include "./application/controllers/SimilarityController.h"
#include "./domain/entities/UGraph.h"

using namespace std;

int main() {
    filesystem::path basePath = "../resources/datasets/original/java";
    string first = "HelloWorld.java", second = "HelloWorld.java";

    cout << "Welcome to java similarity system" << endl;

    cout << "Enter name of first file: ";
    cin >> first;
    
    cout << "Enter name of second file: ";
    cin >> second;

    filesystem::path firstPath = basePath / (first + ".java");
    filesystem::path secondPath = basePath / (second + ".java");


    CFGBuilderController cfgBuilderController;
    UGraph<string>* firstGraph = cfgBuilderController.getGraph(firstPath);
    UGraph<string>* secondGraph = cfgBuilderController.getGraph(secondPath);

    cout << "Debug graph1\n" << firstGraph->toString() << endl;\
    cout << "Debug graph2\n" << secondGraph->toString() << endl;

    SimilarityController similarityController;
    similarityController.getSimilarity(firstGraph, secondGraph);
   


    cout << "Calculated Similarity: " << similarityController.getSimilarity(firstGraph, secondGraph) << endl;

    return 0;
}