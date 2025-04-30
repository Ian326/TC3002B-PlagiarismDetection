#ifndef ABSTRACTSYNTAXTREE_H
#define ABSTRACTSYNTAXTREE_H


/**
 * @class AbstractSyntaxTree
 * @brief This class builds and AST.
 */
class AbstractSyntaxTree {
    private:
        int deleteThis;
        
    public:
        AbstractSyntaxTree();
        ~AbstractSyntaxTree();
};


/**
 * @brief Constructor for the AbstractSyntaxTree class.
 */
AbstractSyntaxTree::AbstractSyntaxTree(){}


/**
 * @brief Destructor for the AbstractSyntaxTree class.
 */
AbstractSyntaxTree::~AbstractSyntaxTree(){}

#endif // ABSTRACTSYNTAXTREE_H