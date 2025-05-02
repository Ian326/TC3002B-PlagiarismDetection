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
        void ifStatementAnalyzer(AbstractSyntaxTree*, UGraph<std::string>*, int&, TreeNode*, std::vector<std::pair<int, std::string>>&);
    
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
    std::set<std::string>::iterator it;
    std::stack<TreeNode*> treeStack;
    int count = 0; // No. de nodo (para diferenciar aquellos con la misma tag)

    std::vector<std::pair<int, std::string>> prevVertexes({std::make_pair(count, "Entry")});
    treeStack.push(tree->getRoot());

    while(!treeStack.empty()) {
        TreeNode* currentNode = treeStack.top();
        treeStack.pop();

        if (currentNode->getTag() == "block") {
            for(TreeNode* child : tree->getChildren(currentNode)) {
                // If in ignoredWords, skip this process
                it = ignoredWords.find(child->getTag());
                if (it != ignoredWords.end()) continue;

                if (child->getTag() == "if_statement") {
                    ifStatementAnalyzer(tree, graph, count, child, prevVertexes);
                } else {
                    std::string tag = blockAnalyzer(tree, child);
                    // Connect resulting tag with all prevVertexes
                    ++count;
                    for(std::pair<int, std::string> vertex : prevVertexes) {
                        std::cout << "coNECTANDO " << vertex.first << " a " << tag << std::endl;
                         graph->addEdge(vertex, std::make_pair(count, tag));
                    }
                    // Make yourself the new prev
                    prevVertexes.clear();
                    prevVertexes.push_back(std::make_pair(count, tag));
                }
            }
        } else { // If not a block, puch children to keep processing missing nodes
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

        if (tree->getChildren(target).empty()) { // Si es una hoja
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


/**
 * @brief Control flow analysis for if
 * @param tree
 * @param graph
 * @param count
 * @param subTreeRoot
 * @param prevVertexes
 */
void CFGBuilderService::ifStatementAnalyzer(AbstractSyntaxTree* tree, UGraph<std::string>* graph, int& count, TreeNode* subTreeRoot, std::vector<std::pair<int, std::string>>& prevVertexes){
    std::vector<std::string> expression_statements; // To store if and else resulting tags
    std::stack<TreeNode *> subTreeStack;
    std::string newTag = "";

    subTreeStack.push(subTreeRoot);

    while (!subTreeStack.empty()) {
        TreeNode *target = subTreeStack.top();
        subTreeStack.pop();

        for (TreeNode *child : tree->getChildren(target)) {
            // Procesamos la condición del if
            if (child->getTag() == "parenthesized_expression") {
                std::string tag = blockAnalyzer(tree, child);

                // Connect resulting tag with all prevVertexes
                ++count;
                for(std::pair<int, std::string> vertex : prevVertexes) {
                    std::cout << "coNECTANDO " << vertex.first << " a " << tag << std::endl;
                    graph->addEdge(vertex, std::make_pair(count, tag));
                }
                // Make yourself the new prev
                prevVertexes.clear();
                prevVertexes.push_back(std::make_pair(count, tag));
            } else if (child->getTag() == "block") {
                expression_statements.push_back(blockAnalyzer(tree, child));
            }
        }
    }
    
    int if_statement = ++count;
    int else_statement = ++count;
    for(std::pair<int, std::string> vertex : prevVertexes) {
        std::cout << "coNECTANDO " << vertex.first << " a " << expression_statements[0] << std::endl;
        std::cout << "coNECTANDO " << vertex.first << " a " << expression_statements[1] << std::endl;
        graph->addEdge(vertex, std::make_pair(if_statement, expression_statements[0]));
        graph->addEdge(vertex, std::make_pair(else_statement, expression_statements[1]));
    }
    prevVertexes.clear();
    prevVertexes.push_back(std::make_pair(count - 1, expression_statements[0]));
    prevVertexes.push_back(std::make_pair(count, expression_statements[1]));
}

std::set<std::string> CFGBuilderService::reservedWords = []() {
    std::set<std::string> aux;

    aux.insert("local_variable_declaration");
    aux.insert("parenthesized_expression");
    aux.insert("expression_statement");
    aux.insert("return-statement");

    return aux;
}();

std::set<std::string> CFGBuilderService::ignoredWords = []() {
    std::set<std::string> aux;

    aux.insert("{");
    aux.insert("}");
    aux.insert(";");
    aux.insert("\"");

    return aux;
}();

#endif // CFGBUILDERSERVICE_H