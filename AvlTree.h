//
// Created by Dell G-3 on 07.10.2019.
//

#ifndef TREESDRAWER_AVLTREE_H
#define TREESDRAWER_AVLTREE_H

class AvlTreeNode {
private:

public:
    int value, height;
    AvlTreeNode * left, * right;
    AvlTreeNode(int, AvlTreeNode *, AvlTreeNode *);
//    ~AvlTreeNode();
};

class AvlTree {
private:
public:
    AvlTreeNode * root;
    AvlTree();
    ~AvlTree();
    void insert(int);
    void erase(int);
};


#endif //TREESDRAWER_AVLTREE_H
