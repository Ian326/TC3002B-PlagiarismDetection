#ifndef TREENODE_H
#define TREENODE_H

#include <vector>


/**
 * @class TreeNode
 * @brief This class represents a node of an AST.
 */
class TreeNode {
    friend class AbstractSyntaxTree;
    
    private:
        std::string tag;
        std::vector<TreeNode*> childs;
        void addChild(TreeNode*);
        
    public:
        TreeNode(std::string tag);
        ~TreeNode();
        std::string getTag();
};


/**
 * @brief Constructor for the TreeNode class.
 */
TreeNode::TreeNode(std::string tag) {
    this->tag = tag;
}


/**
 * @brief Destructor for the TreeNode class.
 */
TreeNode::~TreeNode(){}


/**
 * @brief Add child into childs list
 * @param child Node to be added
 */
void TreeNode::addChild(TreeNode* child) {    
    this->childs.push_back(child);
}


/**
 * @brief Getter for node tag
 * @return node tag
 */
std::string TreeNode::getTag() {
    return this->tag;
}

#endif // TREENODE_H