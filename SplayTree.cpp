//
// Created by Dell G-3 on 16.10.2019.
//
#include <utility>
 using std::pair;

class SplayTreeNode {
public:
    int value;
    SplayTreeNode * right, * left, * parent;
    SplayTreeNode() {
        left = right = parent = nullptr;
    }
};
class SplayTree {
public:
    SplayTreeNode * root;
    SplayTree() {
        root = nullptr;
    }
    void rotateLeft(SplayTreeNode * v) {
        SplayTreeNode * parent = v -> parent,
                * rightNode = v -> right;
        if (parent != nullptr) {
            if (parent -> left == v)
                parent -> left = rightNode;
            else
                parent -> right = rightNode;
        }
        SplayTreeNode * tmp = rightNode -> left;
        rightNode -> left = v;
        v -> right = tmp;
        v -> parent = rightNode;
        rightNode -> parent = parent;
        if (v -> right != nullptr)
            tmp -> parent = v;
        return;
    }
    void rotateRight(SplayTreeNode * v) {
        SplayTreeNode * parent = v -> parent,
                * leftNode = v -> left;
        if (parent != nullptr) {
            if (parent -> left == v)
                parent -> left = leftNode;
            else
                parent -> right = leftNode;
        }
        SplayTreeNode * tmp = leftNode -> right;
        leftNode -> right = v;
        v -> left = tmp;
        v -> parent = leftNode;
        leftNode -> parent = parent;
        if (v -> left != nullptr)
            tmp -> parent = v;
        return;
    }
    void splay(SplayTreeNode * v) {
        if (v == nullptr)
            return;
        while (v -> parent != nullptr) {
            if (v == v -> parent -> left) {
                if (v -> parent -> parent == nullptr)
                    rotateRight(v -> parent);
                else if (v -> parent == v -> parent -> parent -> left) {
                    rotateRight(v -> parent -> parent);
                    rotateRight(v -> parent);
                } else {
                    rotateRight(v -> parent);
                    rotateLeft(v -> parent);
                }
            } else {
                if (v -> parent -> parent == nullptr)
                    rotateLeft(v -> parent);
                else if (v -> parent == v -> parent -> parent -> right) {
                    rotateLeft(v -> parent -> parent);
                    rotateLeft(v -> parent);
                } else {
                    rotateLeft(v -> parent);
                    rotateRight(v -> parent);
                }
            }
        }
    }
    SplayTreeNode * findNode(SplayTreeNode* v, int key) {
        if (v == nullptr)
            return nullptr;
        if (v -> value > key)
            return findNode(v ->left, key);
        else if (v -> value < key)
            return findNode(v ->right, key);
        else return v;
    }
    SplayTreeNode * merging(SplayTreeNode* r1, SplayTreeNode * r2) {
        SplayTreeNode * tmp = r1;
        while (tmp -> right != nullptr)
            tmp = tmp -> right;
        tmp -> right = r2;
        if (r2 != nullptr)
            r2 -> parent = tmp;
        splay(tmp);
        return tmp;
    }
//    pair<SplayTreeNode *, SplayTreeNode *> split(SplayTreeNode * r, int x) {
//        SplayTreeNode *lp, *rp;
//        if (tmp == nullptr) return {r, nullptr};
//        splay(tmp);
//        lp = tmp -> left;
//        rp = tmp -> right;
//        delete tmp;
//        return {rp, lp};
//    }
//    void insert()
};
