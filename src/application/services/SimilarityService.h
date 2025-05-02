#ifndef SIMILARITYSERVICE_H
#define SIMILARITYSERVICE_H

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include "../../domain/entities/UGraph.h"


/**
 * @class SimilarityService
 * @brief This class computes similarity between two files
 */
class SimilarityService {
    private:
        std::vector<std::string> getBagOfTokens(UGraph<std::string>*, UGraph<std::string>*);
        void fillMatrix(std::vector<std::string>&, std::vector<std::vector<double>>&, UGraph<std::string>*);

    public:
        SimilarityService();
        ~SimilarityService();
        double getSimilarity(UGraph<std::string>*, UGraph<std::string>*);
};


/**
 * @brief Constructor for the SimilarityService class.
 */
SimilarityService::SimilarityService(){}


/**
 * @brief Destructor for the SimilarityService class.
 */
SimilarityService::~SimilarityService(){}


/**
 * @brief  Get the bag of tokens from two graphs.
 * @param cfg1 1st graph
 * @param cfg2 2nd graph
 * @return Unique tokens between the two graphs
 */
std::vector<std::string> SimilarityService::getBagOfTokens(UGraph<std::string>* cfg1, UGraph<std::string>* cfg2) {
    std::set<std::string> bagOfTokens;
    
    for(std::string s : cfg1->getVertexes()) {
        bagOfTokens.insert(s);
    }

    for(std::string s : cfg2->getVertexes()) {
        bagOfTokens.insert(s);
    }

    std::vector<std::string> result(bagOfTokens.begin(), bagOfTokens.end());
    return result;
}


/**
 * @brief Set the probability of each node to be the movement of the previous
 * @param bagOfTokens Unique tokes on the graph
 * @param matrix Empty matrix to fill
 * @param cfg Graph that contains each node's movement
 * @return Matrix with movement's probabilities
 */
void SimilarityService::fillMatrix(std::vector<std::string>& bagOfTokens, std::vector<std::vector<double>>& matrix, UGraph<std::string>* graph) {
    std::vector<std::string> vertexes = graph->getVertexes();
    std::vector<std::string>::iterator it;
    for (int i = 0; i < bagOfTokens.size(); i++) {
        it = find(vertexes.begin(), vertexes.end(), bagOfTokens[i]);
        if (it == vertexes.end()) continue;
        
        for (int j = 0; j < bagOfTokens.size(); j++) {
            std::vector<std::string> connections = graph->getConnectionFrom(bagOfTokens[i]);
            it = find(connections.begin(), connections.end(), bagOfTokens[j]);
        if (it == connections.end()) continue;
            matrix[i][j] = 1.0 / connections.size();
        }
    }
}


/**
 * @brief Use Markov to determine similarity between graphs
 * @param cfg1 Base cfg
 * @param cfg2 Cfg to compare
 * @return Similarity between 0 and 1
 */
double SimilarityService::getSimilarity(UGraph<std::string>* cfg1, UGraph<std::string>* cfg2) {
    std::vector<std::string> bagOfTokens = getBagOfTokens(cfg1, cfg2);

    std::vector<std::vector<double>> matrix1(bagOfTokens.size(), std::vector<double>(bagOfTokens.size()));
    std::vector<std::vector<double>> matrix2(bagOfTokens.size(), std::vector<double>(bagOfTokens.size()));
    
    fillMatrix(bagOfTokens, matrix1, cfg1);
    fillMatrix(bagOfTokens, matrix2, cfg2);

    std::vector<double> flattened1, flattened2;
    for (int i = 0; i < bagOfTokens.size(); i++) {
        flattened1.insert(flattened1.end(), matrix1[i].begin(), matrix1[i].end());
        flattened2.insert(flattened2.end(), matrix2[i].begin(), matrix2[i].end());
    }

    double magnitude1 = 0.0, magnitude2 = 0.0;
    for(double elem : flattened1) {
        magnitude1 += elem * elem;
    }
    magnitude1 = sqrt(magnitude1);

    for(double elem : flattened2) {
        magnitude2 += elem * elem;
    }
    magnitude2 = sqrt(magnitude2);

    if (!magnitude1 || !magnitude2)
        return 0.0;

    double producto_punto = std::inner_product(flattened1.begin(), flattened1.end(), flattened2.begin(), 0.0);

    return producto_punto/(magnitude1*magnitude2);
}

#endif // SIMILARITYSERVICE_H