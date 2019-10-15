//
// Created by Dell G-3 on 07.10.2019.
//

#ifndef TREESDRAWER_REDBLACKTREE_H
#define TREESDRAWER_REDBLACKTREE_H

class RedBlackTreeNode {
public:
    bool color;//0 - black; 1 - red
    int value;
    RedBlackTreeNode *left, *right, *parent;

    RedBlackTreeNode(int, bool, RedBlackTreeNode *, RedBlackTreeNode *);
    RedBlackTreeNode();
};

class RedBlackTree {
private:
    RedBlackTreeNode * root, *nil;
    void deleting(RedBlackTreeNode*);
    void leftRotate();
    void rightRotate();
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(int);
    void erase(int);
    RedBlackTreeNode* search(int);
};


#endif //TREESDRAWER_REDBLACKTREE_H
