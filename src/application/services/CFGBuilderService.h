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
        void blockAnalyzer(AbstractSyntaxTree*, UGraph<std::string>*, int&, TreeNode*, std::vector<std::pair<int, std::string>>&);
        std::string leavesTraveler(AbstractSyntaxTree*, TreeNode*);
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
UGraph<std::string>* CFGBuilderService::build(AbstractSyntaxTree* tree) {
    UGraph<std::string>* graph = new UGraph<std::string>(true);
    int count = 0; // No. de nodo (para diferenciar aquellos con la misma tag)

    // Nodos de entrada. Estos se conectaran a los nodos siguientes eventualmente
    std::vector<std::pair<int, std::string>> prevVertexes({std::make_pair(count, "Entry")});
    count++;
    std::stack<TreeNode*> treeStack;

    treeStack.push(tree->getRoot());

    while(!treeStack.empty()) {
        TreeNode* currentNode = treeStack.top();
        treeStack.pop();

        if (currentNode->getTag() == "block") {
            blockAnalyzer(tree, graph, count, currentNode, prevVertexes);
        } else {
            for(TreeNode* child : tree->getChildren(currentNode)) {
                treeStack.push(child);
            }
        }
    }
    return graph;
}

void CFGBuilderService::blockAnalyzer(AbstractSyntaxTree* tree, UGraph<std::string>* graph, int& count, TreeNode* subTreeRoot, std::vector<std::pair<int, std::string>>& prevVertexes) {
    std::set<std::string>::iterator it;
    for(TreeNode* child : tree->getChildren(subTreeRoot)) {
        // If in ignoredWords, skip this process
        it = ignoredWords.find(child->getTag());
        if (it != ignoredWords.end()) continue;

        if (child->getTag() == "if_statement") {
            ifStatementAnalyzer(tree, graph, count, child, prevVertexes);
        } else {
            std::string tag = leavesTraveler(tree, child);
            // Connect resulting tag with all prevVertexes
            for(std::pair<int, std::string> vertex : prevVertexes) {
                std::cout << "coNECTANDO " << vertex.first << " a " << tag << std::endl;
                    graph->addEdge(vertex, std::make_pair(count, tag));
            }
            // Make yourself the new prev
            prevVertexes.clear();
            prevVertexes.push_back(std::make_pair(count, tag));
            count++;
        }
    }    
}

/**
 * @brief Control flow analysis for blocks
 * @param tree AST being analyzed
 * @param subTreeRoot block starting point
 * @return tag formed by combining all leaf nodes of given root
 */
std::string CFGBuilderService::leavesTraveler(AbstractSyntaxTree* tree, TreeNode* subTreeRoot) {
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
    std::vector<std::pair<int, std::string>> expression_statements; // To store if and else resulting tags
    std::stack<TreeNode *> subTreeStack;
    std::vector<std::pair<int, std::string>>prevVertexesCopy;
    std::vector<std::pair<int, std::string>>statementsStart;
    std::pair<int, std::string> parenthesizedExpression;
    std::string tag, newTag = "";
    int auxCount;

    subTreeStack.push(subTreeRoot);

    while (!subTreeStack.empty()) {
        TreeNode *target = subTreeStack.top();
        subTreeStack.pop();

        for (TreeNode *child : tree->getChildren(target)) {
            // Procesamos la condición del if
            if (child->getTag() == "parenthesized_expression") {
                tag = leavesTraveler(tree, child);
                parenthesizedExpression = make_pair(count, tag);
                
                std::cout << "guardandooo " << tag << std::endl;
                // Connect resulting tag with all prevVertexes
                for(std::pair<int, std::string> vertex : prevVertexes) {
                    std::cout << "coNECTANDO " << vertex.first << " a " << tag << std::endl;
                    graph->addEdge(vertex, std::make_pair(count, tag));
                }
                // Make yourself the new prev
                prevVertexes.clear();
                prevVertexes.push_back(std::make_pair(count, tag));
                count++;
            } else if (child->getTag() == "block") {
                int countCopy = count;
                blockAnalyzer(tree, graph, count, child, prevVertexes);
                statementsStart.push_back(std::make_pair(countCopy, graph->getTagFrom(countCopy)));
                prevVertexesCopy.push_back(graph->getLastNode());
            }
        }
    }

    for (std::pair<int, std::string> p: statementsStart){
        graph->addEdge(parenthesizedExpression, p);
    }
    std::cout << "cosas raras" << std::endl;
     std::cout << "coNECTANDO " << parenthesizedExpression.first << " a " << statementsStart[0].second << std::endl;
    std::cout << "coNECTANDO " << parenthesizedExpression.first << " a " << statementsStart[1].second << std::endl;
    
    prevVertexes = prevVertexesCopy;
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