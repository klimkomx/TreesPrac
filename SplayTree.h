//
// Created by Dell G-3 on 16.10.2019.
//

#ifndef TREESDRAWER_SPLAYTREE_H
#define TREESDRAWER_SPLAYTREE_H

class SplayTreeNode {
public:
    SplayTreeNode* parent, *right, *left;
    int value;
};

class SplayTree {
private:
    SplayTreeNode* root;
    void rotate(SplayTreeNode *, SplayTreeNode *);
    SplayTreeNode * splay(SplayTreeNode *);
    SplayTreeNode * find(SplayTreeNode *);
    SplayTreeNode * split(SplayTreeNode *);
    SplayTreeNode * merge(SplayTreeNode *);
    SplayTreeNode * remove(SplayTreeNode *);
public:
    SplayTree();
    bool remove(int elem);
    bool search(int elem);
    bool insert(int element);
};


#endif //TREESDRAWER_SPLAYTREE_H
