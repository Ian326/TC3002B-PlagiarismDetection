#ifndef CFGBUILDERSERVICE_H
#define CFGBUILDERSERVICE_H

#include<string>
#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../../domain/entities/UGraph.h"

/**
 * @class CFGBuilderService
 * @brief This class builds an CFG from a given AST.
 */
class CFGBuilderService {
    public:
        CFGBuilderService();
        ~CFGBuilderService();
        UGraph<std::string>* build(AbstractSyntaxTree*);
};


/**
 * @brief Constructor for the CFGBuilderService class.
 */
CFGBuilderService::CFGBuilderService(){}


/**
 * @brief Destructor for the CFGBuilderService class.
 */
CFGBuilderService::~CFGBuilderService(){}

UGraph<std::string>* build(AbstractSyntaxTree*);

#endif // CFGBUILDERSERVICE_H