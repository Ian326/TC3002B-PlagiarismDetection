#ifndef CFGBUILDERSERVICE_H
#define CFGBUILDERSERVICE_H

#include <string>
#include <stack>
#include <iterator>
#include <set>
#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../../domain/entities/TreeNode.h"
#include "../../domain/entities/UGraph.h"


/**
 * @class CFGBuilderService
 * @brief This class builds an CFG from a given AST.
 */
class CFGBuilderService {
    private:
        static std::set<std::string> reservedWords;
        static std::set<std::string> ignoredWords;
    
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


/**
 * @brief Construct CFG from AST
 * @param tree input AST
 * @return Resulting UGraph
 */
UGraph<std::string>* CFGBuilderService::build(AbstractSyntaxTree* tree){
    UGraph<std::string>* graph = new UGraph<std::string>(true);
    std::string prevVertex = "Entry";
    std::stack<TreeNode*> treeStack;
    
    treeStack.push(tree->getRoot());

    while(!treeStack.empty()) {
        TreeNode* currentNode = treeStack.top();
        treeStack.pop();
        std::set<std::string>::iterator it = reservedWords.find(currentNode->getTag());
        
        // Si encontramos un "block"
        if (it != reservedWords.end()) {
            std::stack<TreeNode*> subTreeStack;
            std::string newTag = "";

            subTreeStack.push(currentNode);
            
            // Combinamos los tags de las hojas
            while(!subTreeStack.empty()) {
                TreeNode* target = subTreeStack.top();
                subTreeStack.pop();

                if (tree->getChildren(target).empty()) {
                    it = ignoredWords.find(target->getTag());

                    if (it == ignoredWords.end())
                        newTag = target->getTag() + newTag;
                } else {
                    for (TreeNode* child : tree->getChildren(target)) {
                        subTreeStack.push(child);
                    }
                }
            } 
            
            graph->addEdge(prevVertex, newTag);
            prevVertex = newTag;
        } else {
            for(TreeNode* child : tree->getChildren(currentNode)) {
                treeStack.push(child);
            }
        }
    }
    return graph;
}

std::set<std::string> CFGBuilderService::reservedWords = []() {
    std::set<std::string> aux;

    aux.insert("block");

    return aux;
}();

std::set<std::string> CFGBuilderService::ignoredWords = []() {
    std::set<std::string> aux;

    aux.insert("{");
    aux.insert("}");
    aux.insert(";");

    return aux;
}();

#endif // CFGBUILDERSERVICE_H