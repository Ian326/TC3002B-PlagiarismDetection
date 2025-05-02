#ifndef CFGBUILDERCONTROLLER_H
#define CFGBUILDERCONTROLLER_H

#include<string>
#include "../../domain/entities/UGraph.h"
#include "../services/CFGBuilderService.h"


/**
 * @class CFGBuilderController
 * @brief This class calls service to build a CFG from an AST.
 */
class CFGBuilderController {
    public:
        CFGBuilderController();
        ~CFGBuilderController();
        UGraph<std::string>* getGraph(std::filesystem::path&); 
};


/**
 * @brief Constructor for the CFGBuilderController class.
 */
CFGBuilderController::CFGBuilderController(){}


/**
 * @brief Destructor for the CFGBuilderController class.
 */
CFGBuilderController::~CFGBuilderController(){}


/**
 * @brief Call CFGBuilderService to generate Control Flow Graph.
 * @param ast ast to process
 * @return UGraph representing the CFG
 */
UGraph<std::string>* CFGBuilderController::getGraph(std::filesystem::path& sourceCode) {
    CFGBuilderService builder;
    return builder.build(sourceCode);
}

#endif // CFGBUILDERCONTROLLER_H