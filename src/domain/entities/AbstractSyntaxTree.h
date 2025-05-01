#ifndef ABSTRACTSYNTAXTREE_H
#define ABSTRACTSYNTAXTREE_H

#include "./TreeNode.h"
#include "../services/StringService.h"


/**
 * @class AbstractSyntaxTree
 * @brief This class builds an AST.
 */
class AbstractSyntaxTree {
    private:
        TreeNode* root;
        
    public:
        AbstractSyntaxTree(TreeNode* root);
        ~AbstractSyntaxTree();
        TreeNode* getRoot();
        std::vector<TreeNode*> getChildren(TreeNode* parent);
        void addChild(TreeNode* parent, TreeNode* child);
        std::string toString(std::string, TreeNode* node, int level);
};


/**
 * @brief Constructor for the AbstractSyntaxTree class.
 */
AbstractSyntaxTree::AbstractSyntaxTree(TreeNode* root) {
    this->root = root;
}


/**
 * @brief Destructor for the AbstractSyntaxTree class.
 */
AbstractSyntaxTree::~AbstractSyntaxTree(){}


/**
 * @brief Get the root of the AST
 * @return Root node of the AST
 */
TreeNode* AbstractSyntaxTree::getRoot() {
    return this->root;
}


/**
 * @brief Get children of a Node in the AST
 * @param parent Parent node
 * @return TreeNode vector referencing all child nodes
 */
std::vector<TreeNode*> AbstractSyntaxTree::getChildren(TreeNode* parent) {
    return parent->childs;
}


/**
 * @brief Add a child Node into a Node in the AST
 * @param parent Parent node
 * @param child Child node to be added
 */
void AbstractSyntaxTree::addChild(TreeNode* parent, TreeNode* child) {
    parent->childs.push_back(child);
}


/**
 * @brief Print the AST in pre-order. Each level is indented with spaces.
 * @param node Node to be printed
 * @param level Level of the node in the tree
 */
 std::string AbstractSyntaxTree::toString(std::string treeString, TreeNode* node, int level) {
    if (!node) {
        return treeString;
    }

    TreeNode* aux = node;
    treeString += StringService::characterRepeater('.', level) + aux->getTag() + "\n";

    for (TreeNode* child : aux->childs) {
        treeString = toString(treeString, child, level + 1);
    }

    return treeString;
}


#endif // ABSTRACTSYNTAXTREE_H