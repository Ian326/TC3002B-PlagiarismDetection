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
        std::string blockAnalyzer(AbstractSyntaxTree*, TreeNode*);
    
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
    int count = 0;
    std::pair<int, std::string> prevVertex = std::make_pair(count, "Entry");
    std::stack<TreeNode*> treeStack;
    
    treeStack.push(tree->getRoot());

    while(!treeStack.empty()) {
        TreeNode* currentNode = treeStack.top();
        treeStack.pop();
        std::set<std::string>::iterator it = reservedWords.find(currentNode->getTag());
        
        if (it != reservedWords.end()) {
            if (currentNode->getTag() == "block") {
                for(TreeNode* child : tree->getChildren(currentNode)){
                    std::set<std::string>::iterator itr = ignoredWords.find(child->getTag());
                    if (itr != ignoredWords.end()) continue;
                
                    std::string tag = blockAnalyzer(tree, child);
                    
                    graph->addEdge(prevVertex, make_pair(++count, tag));
                    prevVertex = make_pair(count, tag);
                    
                }
            }
        } else {
            for(TreeNode* child : tree->getChildren(currentNode)) {
                treeStack.push(child);
            }
        }
    }
    return graph;
}


/**
 * @brief Control flow analysis for blocks
 * @param tree AST being analyzed
 * @param subTreeRoot block starting point
 * @return tag formed by combining all leaf nodes of given root
 */
std::string CFGBuilderService::blockAnalyzer(AbstractSyntaxTree* tree, TreeNode* subTreeRoot) {
    std::stack<TreeNode *> subTreeStack;
    std::string newTag = "";

    subTreeStack.push(subTreeRoot);

    // Combinamos los tags de las hojas
    while (!subTreeStack.empty()) {
        TreeNode *target = subTreeStack.top();
        subTreeStack.pop();

        if (tree->getChildren(target).empty())
        {
            std::set<std::string>::iterator it = ignoredWords.find(target->getTag());

            if (it == ignoredWords.end())
                newTag = target->getTag() + newTag;
        } else {
            for (TreeNode *child : tree->getChildren(target)) {
                subTreeStack.push(child);
            }
        }
    }
        return newTag;
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