#ifndef SIMILARITYCONTROLLER_H
#define SIMILARITYCONTROLLER_H

#include <string>
#include "../../domain/entities/UGraph.h"
#include "../services/SimilarityService.h"


/**
 * @class SimilarityController
 * @brief This class calls service to compute similarity.
 */
class SimilarityController {
    public:
        SimilarityController();
        ~SimilarityController(); 
        double getSimilarity(UGraph<std::string>* cfg1, UGraph<std::string>* cfg2);
};


/**
 * @brief Constructor for the SimilarityController class.
 */
SimilarityController::SimilarityController(){}


/**
 * @brief Destructor for the SimilarityController class.
 */
SimilarityController::~SimilarityController(){}


/**
 * @brief Call SimilarityService to compute similarity.
 * @param cfg1 Base cfg
 * @param cfg2 Cfg to compare
 * @return Similarity between 0 and 1
 */
double SimilarityController::getSimilarity(UGraph<std::string>* cfg1, UGraph<std::string>* cfg2) {
    SimilarityService computeSimilarity;
    return computeSimilarity.getSimilarity(cfg1, cfg2);
}

#endif // SIMILARITYCONTROLLER_H