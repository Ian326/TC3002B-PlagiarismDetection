#ifndef ABSTRACTSYNTAXTREE_H
#define ABSTRACTSYNTAXTREE_H

#include "./TreeNode.h"


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
        void addChild(TreeNode* parent, TreeNode* child);
        void print(TreeNode* node, int level);
};


/**
 * @brief Constructor for the AbstractSyntaxTree class.
 */
AbstractSyntaxTree::AbstractSyntaxTree(TreeNode* root){
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
void AbstractSyntaxTree::print(TreeNode* node, int level=0) { 
    TreeNode* aux = node;
    std::cout << aux -> getTag();

    for (TreeNode* childs : aux->childs){
        print(aux, level + 1);
    }
}


#endif // ABSTRACTSYNTAXTREE_H