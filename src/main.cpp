#include <bits/stdc++.h>

#include "./application/controllers/CFGBuilderController.h"
#include "./application/controllers/SimilarityController.h"
#include "./domain/entities/UGraph.h"
#include "./domain/services/StringService.h"

using namespace std;

void play(){
    filesystem::path basePath = "../resources/datasets/";
    string first = "T1", second = "T2";

    filesystem::path firstPath = basePath / (first + ".java");
    filesystem::path secondPath = basePath / (second + ".java");

    CFGBuilderController cfgBuilderController;
    UGraph<string>* firstGraph = cfgBuilderController.getGraph(firstPath);
    UGraph<string>* secondGraph = cfgBuilderController.getGraph(secondPath);


    SimilarityController similarityController;
    similarityController.getSimilarity(firstGraph, secondGraph);
   

    cout << "Calculated Similarity: " << similarityController.getSimilarity(firstGraph, secondGraph) << endl;
};

void test() {
    filesystem::path testBasePath = "../resources/datasets/IR-Plag-Dataset";
    filesystem::path original, plagiarized, nonPlagiarized;

    UGraph<string>* originalGraph;
    UGraph<string>* plagiarizedGraph;

    CFGBuilderController cfgBuilderController;
    SimilarityController similarityController;
    
    double isPlagiarized = 0.75;
    int successPlag = 0, successNonPlag = 0;
    int totalPlag = 0, totalNonPlag = 0;
    int error = 0;

    try {
        for (const auto & testCase : filesystem::directory_iterator(testBasePath)) {
            error = 0;
            cout << "CARPETA A ANALIZAR: " << testCase.path() << endl;

            for (const auto & baseFile : filesystem::directory_iterator(testCase.path() / "original")) {
                cout << "ORIGINAL: " << baseFile.path().string() << endl;
                original = baseFile.path();  
            }
            originalGraph = cfgBuilderController.getGraph(original);

            // non-plagiarized

            for (const auto & plagFile : filesystem::directory_iterator(testCase.path() / "plagiarized")) {
                if(is_regular_file(plagFile)) {
                    cout << "PLAGIO: " << plagFile.path().filename().string() << endl;
                    plagiarized = plagFile.path();

                    plagiarizedGraph = cfgBuilderController.getGraph(plagiarized);

                    int similarity = similarityController.getSimilarity(originalGraph, plagiarizedGraph);
                    successPlag += (similarity >= isPlagiarized)? 1 : 0;
                    cout << "Plagiarized similarity: " << similarity << endl;
                    totalPlag++;
                }   
            }
            cout << "Plagiarized detection accuracy: " << (double)successPlag / totalPlag << "\n\n\n";
        }

        /*for (const auto & file : filesystem::directory_iterator(originalBasePath)) {
            cout << "TEST file: " << file.path().filename().string() << endl;

            filesystem::path original = originalBasePath / file.path().filename();
            filesystem::path plagiarized = plagiarizedBasePath / file.path().filename();
            filesystem::path nonPlagiarized = nonPlagiarizedBasePath / file.path().filename();

            try {
                UGraph<string>* originalGraph = cfgBuilderController.getGraph(original);
                UGraph<string>* plagiarizedGraph = cfgBuilderController.getGraph(plagiarized);
                UGraph<string>* nonPlagiarizedGraph = cfgBuilderController.getGraph(nonPlagiarized);

                int similarity;
                similarity = similarityController.getSimilarity(originalGraph, plagiarizedGraph);
                success += (similarity >= isPlagiarized)? 1 : 0;
                cout << "plagiarized" << similarity << endl;

                similarityController.getSimilarity(originalGraph, nonPlagiarizedGraph);
                success += (similarity < isPlagiarized)? 1 : 0;
                
                cout << similarity << endl;
                total += 2;
            } catch (const std::exception& e) {
                // Handle standard exceptions
                cerr << "Error: while transforming " << file << endl;
                continue;
            } 
        }

        cout << "Accuracy: " << (double)success / total << endl;*/
    } catch (const std::exception& e) {
        // Handle standard exceptions
        cerr << "Error while processing test case" << endl;
    } 
};

int main() {

    int option;
    cout << "Welcome to java similarity system" << endl;

    do {
        cout << "Play[1]\nTest[2]\nExit[3]\n\nSelect option: ";

        cin >> option;
        if (option == 1){
            play();
        } else if (option == 2){
            test();
        }
        else if (option == 3){
            break;
        }
        
    } while (true);
   
    return 0;
}