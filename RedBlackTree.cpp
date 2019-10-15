//
// Created by Dell G-3 on 07.10.2019.
//

#include "RedBlackTree.h"

//Constructors/Destructors

RedBlackTreeNode::RedBlackTreeNode(int key, bool colorr, RedBlackTreeNode* leftt, RedBlackTreeNode* rightt) {
    value = key;
    parent = nullptr;
    color = colorr;
    left = leftt;
    right = rightt;
    return;
}

RedBlackTreeNode::~RedBlackTreeNode() {
    if (left != nullptr)
        delete left;
    if (right != nullptr)
        delete right;
    delete this;
    return;
}

RedBlackTree::RedBlackTree() {
    root = nil = new RedBlackTreeNode(-1, false, nullptr, nullptr);
    nil -> left = nil -> right = nil;
    return;
}

RedBlackTree::~RedBlackTree() {
    if (root != nullptr)
        delete root;
    else
        delete nil;
    delete this;
    return;
}

//Private Methods

void RedBlackTree::rightRotate(RedBlackTreeNode * tmp) {
    RedBlackTreeNode * ttp;
    if (tmp == root)
        root = tmp -> left;
    else if (tmp -> parent -> left == tmp)
        tmp -> parent -> left = tmp -> left;
    else
        tmp -> parent -> right = tmp -> left;
    tmp -> left -> parent = tmp -> parent;
    tmp -> parent = tmp -> left;
    if (tmp -> left -> right != nullptr)
        tmp -> left -> right -> parent = tmp;
    ttp = tmp -> left;
    tmp -> left = tmp -> left -> right;
    ttp -> right = tmp;
    return;
}

void RedBlackTree::leftRotate(RedBlackTreeNode * tmp) {
    RedBlackTreeNode * ttp;
    if (tmp == root)
        root = tmp -> right;
    else if (tmp -> parent -> right == tmp)
        tmp -> parent -> right = tmp -> right;
    else
        tmp -> parent -> left = tmp -> right;
    tmp -> right -> parent = tmp -> parent;
    tmp -> parent = tmp -> right;
    if (tmp -> right -> left != nullptr)
        tmp -> right -> left -> parent = tmp;
    ttp = tmp -> right;
    tmp -> right = tmp -> right -> left;
    ttp -> left = tmp;
    return;
}

void RedBlackTree::insertingFix(RedBlackTreeNode * node) {
    RedBlackTreeNode * uncle, * father, * grandfather;
    while (node -> parent -> color) {
        father = node -> parent;
        grandfather = father -> parent;
        if (grandfather -> left == father) {
            uncle = grandfather -> right;
            if (uncle -> color) {
                uncle -> color = father -> color = false;
                grandfather -> color = true;
            } else {
                if (father -> right == node) {
                    node = father;
                    leftRotate(node);
                }
                node -> parent -> color = false;
                grandfather -> color = true;
                rightRotate(grandfather);
            }
        } else {
            uncle = grandfather -> left;
            if (uncle -> color) {
                uncle -> color = father -> color = false;
                grandfather -> color = true;
            } else {
                if (father -> left == node) {
                    node = father;
                    rightRotate(node);
                }
                node -> parent -> color = false;
                grandfather -> color = true;
                leftRotate(grandfather);
            }
        }
    }
    node -> color = false;
    return;
}

void RedBlackTree::deletingFix(RedBlackTreeNode * x) {
    while (x != root && x -> color == false) {
        RedBlackTreeNode * tmp = nullptr;
        if (x -> parent -> left == x) {
            tmp = x -> parent -> right;
            if (tmp -> color) {
                tmp -> color = false;
                x -> parent -> color = true;
                leftRotate(x -> parent);
            }
            if (!tmp -> left -> color && !tmp -> right -> color) {
                tmp -> color = true;
                x = x -> parent;
                x -> color = false;
            } else {
                if (!tmp -> right -> color) {
                    tmp -> left -> color = false;
                    tmp -> color = true;
                    rightRotate(tmp);
                    tmp = x -> parent -> right;
                }
                tmp -> color = tmp -> parent -> color;
                tmp -> right -> color = x -> parent -> color = false;
                leftRotate(x -> parent);
                x = root;
            }
        } else {
            tmp = x -> parent -> left;
            if (tmp -> color) {
                tmp -> color = false;
                x -> parent -> color = true;
                rightRotate(x -> parent);
            }
            if (!tmp -> left -> color && !tmp -> right -> color) {
                tmp -> color = true;
                x = x -> parent;
                x -> color = false;
            } else {
                if (!tmp->left->color) {
                    tmp->right->color = false;
                    tmp->color = true;
                    leftRotate(tmp);
                    tmp = x->parent->left;
                }
                tmp->color = tmp->parent->color;
                tmp->left->color = x->parent->color = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x -> color = false;
    return;
}

//Public Methods

RedBlackTreeNode* RedBlackTree::search(int key) {
    RedBlackTreeNode * tmp = root;
    while (tmp != nil && tmp -> value != key) {
        if (tmp -> value < key)
            tmp = tmp -> right;
        else
            tmp = tmp -> left;
    }
    return tmp;
}

void RedBlackTree::insert(int key) {
    RedBlackTreeNode *insertingElement = new RedBlackTreeNode(key, 1, nil, nil);
    if (root == nil) {
        root = insertingElement;
        root -> color = 0;
        return;
    } else {
        RedBlackTreeNode *iterator1 = root, *iterator2 = nil;
        while (iterator1 != nil) {
            iterator2 =iterator1;
            if (iterator1->value < key)
                iterator1 = iterator1 -> right;
            else
                iterator1 = iterator1 -> left;
        }
        insertingElement -> parent = iterator2;
        if (iterator2->value < insertingElement -> value)
            iterator2 -> right = insertingElement;
        else
            iterator2 -> left = insertingElement;
        insertingFix(insertingElement);
    }
}

void RedBlackTree::erase(int key) {
    RedBlackTreeNode * z = search(key), *x = nil, *chosen = nil;
    if (z == nil)
        return;
    if (z -> left == nil || z -> right == nil)
        chosen = z;
    else {
        chosen == z -> right;
        while (chosen -> left != nil)
            chosen = chosen -> left;
    }
    if (chosen -> left != nil)
        x = chosen -> left;
    else
        x = chosen -> right;
    x -> parent = chosen -> parent;
    if (chosen -> parent == nil)
        root = x;
    else {
        if (chosen == chosen -> parent -> left)
            chosen -> parent -> left = x;
        else
            chosen -> parent -> right = x;
    }
    if (chosen != z)
        z -> value = chosen -> value;
    if (chosen -> color == false)
        deletingFix(chosen);
    delete chosen;
    return;
}