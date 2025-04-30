#ifndef ABSTRACTSYNTAXTREE_H
#define ABSTRACTSYNTAXTREE_H

class AbstractSyntaxTree {
    private:
        int deleteThis;
        
    public:
        AbstractSyntaxTree();
        ~AbstractSyntaxTree();
};

AbstractSyntaxTree::AbstractSyntaxTree(){}

AbstractSyntaxTree::~AbstractSyntaxTree(){}

#endif // ABSTRACTSYNTAXTREE_H