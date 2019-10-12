//
// Created by Dell G-3 on 07.10.2019.
//

#ifndef TREESDRAWER_REDBLACKTREE_H
#define TREESDRAWER_REDBLACKTREE_H
namespace RedBlackTreeNode {
    class Node {
    public:
        bool black;
        int value;
        Node *left, *right, *father;

        Node(int, bool, Node *, Node *);
    };
}
class RedBlackTree {
private:
    RedBlackTreeNode::Node* root;
public:
    RedBlackTree() {
        root = nullptr;
    }
    void insert(int);
    void erase(int);
    RedBlackTreeNode::Node* search(int key);
};


#endif //TREESDRAWER_REDBLACKTREE_H
