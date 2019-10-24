//
// Created by Dell G-3 on 07.10.2019.
//

#include "RedBlackTree.h"
#include <algorithm>

//Constructors/Destructors

RedBlackTreeNode::RedBlackTreeNode(int key, bool colorr, RedBlackTreeNode* leftt, RedBlackTreeNode* rightt, RedBlackTreeNode* paren) {
    value = key;
    parent = paren;
    color = colorr;
    left = leftt;
    right = rightt;
    return;
}


RedBlackTree::RedBlackTree() {
    root = nil = new RedBlackTreeNode(-1, false, nullptr, nullptr, nullptr);
    nil -> left = nil -> right = nil;
    return;
}

//RedBlackTree::~RedBlackTree() {
//    if (root != nullptr)
//        delete root;
//    else
//        delete nil;
//    delete this;
//    return;
//}

//Private Methods

void RedBlackTree::rightRotate(RedBlackTreeNode * tmp) {
    RedBlackTreeNode *left_child = tmp -> left;
    tmp -> left = left_child -> right;
    if (tmp == root)
        root = left_child;
    else if (tmp -> parent -> right == tmp)
        tmp -> parent -> right = left_child;
    else
        tmp -> parent -> left = left_child;
    if (tmp -> left != nil) {
        tmp -> left -> parent = tmp;
    }
    left_child -> parent = tmp -> parent;
//    tmp -> right -> parent = tmp -> parent;
//    tmp -> parent = tmp -> right;
    left_child -> right = tmp;
    tmp -> parent = left_child;
//    if (tmp -> right -> left != nil)
//        tmp -> right -> left -> parent = tmp;
//    ttp = tmp -> right;
//    tmp -> right = tmp -> right -> left;
//    ttp -> left = tmp;
    return;
}

void RedBlackTree::leftRotate(RedBlackTreeNode * tmp) {
    RedBlackTreeNode *right_child = tmp -> right;
    tmp -> right = right_child -> left;
    if (tmp == root)
        root = right_child;
    else if (tmp -> parent -> right == tmp)
        tmp -> parent -> right = right_child;
    else
        tmp -> parent -> left = right_child;
    if (tmp -> right != nil) {
        tmp -> right -> parent = tmp;
    }
    right_child -> parent = tmp -> parent;
//    tmp -> right -> parent = tmp -> parent;
//    tmp -> parent = tmp -> right;
    right_child -> left = tmp;
    tmp -> parent = right_child;
//    if (tmp -> right -> left != nil)
//        tmp -> right -> left -> parent = tmp;
//    ttp = tmp -> right;
//    tmp -> right = tmp -> right -> left;
//    ttp -> left = tmp;
    return;    
}

void RedBlackTree::insertingFix(RedBlackTreeNode * node) {
    RedBlackTreeNode * uncle, * father, * grandfather;
    if (node == root) {
        root -> color = false;
        return;
    }
    while (node != root && node -> parent -> color && node ->color) {
        father = node -> parent;
        grandfather = father -> parent;
        if (grandfather -> left == father) {
            uncle = grandfather -> right;
            if (uncle -> color) {
                uncle -> color = father -> color = false;
                grandfather -> color = true;
                node = grandfather;
            } else {
                if (father -> right == node) {
                    node = father;
                    leftRotate(node);
                    father = node -> parent;
                }
                rightRotate(grandfather);
                std::swap(node -> parent -> color, grandfather -> color);
                node = father;
            }
        } else {
            uncle = grandfather -> left;
            if (uncle -> color) {
                uncle -> color = father -> color = false;
                grandfather -> color = true;
                node = grandfather;
            } else {
                if (father -> left == node) {
                    node = father;
                    rightRotate(node);
                    father = node -> parent;
                }
                leftRotate(grandfather);
                std::swap(node -> parent -> color, grandfather -> color);
                node = father;
            }
        }
    }
    root -> color = false;
    return;
}

void RedBlackTree::deletingFix(RedBlackTreeNode * x) {
    RedBlackTreeNode* parent;
    while (x != root && x -> color == false) {
        parent = x -> parent;
        RedBlackTreeNode * tmp = nullptr;
        if (parent -> left == x) {
            tmp = parent -> right;
            if (tmp -> color) {
                tmp -> color = false;
                 parent -> color = true;
                leftRotate(x -> parent);
            } else {
                if (tmp != nil && !tmp -> left -> color && !tmp -> right -> color) {
                    tmp -> color = true;
                    x = parent;
                    x -> color = false;
                } else {
                    if (tmp != nil && !tmp -> right -> color) {
                        tmp -> left -> color = false;
                        tmp -> color = true;
                        rightRotate(tmp);
                        tmp = parent -> right;
                    }
                    tmp -> color = parent -> color;
                    tmp -> right -> color = parent -> color = false;
                    leftRotate(parent);
                    break;
                }
            }
        } else {
            tmp = parent -> left;
            if (tmp -> color) {
                tmp -> color = false;
                parent -> color = true;
                rightRotate(x -> parent);
            } else {
                if (tmp != nil && !tmp -> left -> color && !tmp -> right -> color) {
                    tmp -> color = true;
                    x = parent;
                    x -> color = false;
                } else {
                    if (tmp != nil && !tmp -> left -> color) {
                        tmp -> right -> color = false;
                        tmp -> color = true;
                        leftRotate(tmp);
                        tmp = parent -> left;
                    }
                    tmp -> color = parent -> color;
                    tmp -> left -> color = parent -> color = false;
                    rightRotate(parent);
                    break;
                }
            }
        }
    }
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
    RedBlackTreeNode *insertingElement = new RedBlackTreeNode(key, 1, nil, nil, nil);
    if (root == nil) {
        root = insertingElement;
        root -> color = 0;
        return;
    } else {
        RedBlackTreeNode *iterator1 = root, *iterator2 = nil;
        while (iterator1 != nil) {
            iterator2 =iterator1;
            if (iterator1 -> value == key)
                return;
            if (iterator1->value < key)
                iterator1 = iterator1 -> right;
            else
                iterator1 = iterator1 -> left;
        }
        insertingElement -> parent = iterator2;
        if (iterator2->value < insertingElement -> value) {
            iterator2 -> right -> parent = iterator2;
            iterator2 -> right = insertingElement;
        }
        else {
            iterator2 -> left -> parent = iterator2;
            iterator2 -> left = insertingElement;
        }
        insertingFix(insertingElement);
    }
}

void RedBlackTree::erase(int key) {
    RedBlackTreeNode * z = search(key), *chosen = nil;
    if (z == nil)
        return;
    if (z -> left == nil || z -> right == nil)
        chosen = z;
    else {
        chosen = z -> right;
        while (chosen -> left != nil)
            chosen = chosen -> left;
    }
    std::swap(chosen -> value, z->value);
    if (chosen == root) {
        delete chosen;
        root = nil;
        return;
    }
    if (chosen -> color || chosen -> left -> color|| chosen -> right -> color) {
            RedBlackTreeNode *child = chosen->left != nullptr ? chosen->left : chosen->right;

            if (chosen == chosen->parent->left) {
                chosen->parent->left = child;
            } else {
                chosen->parent->right = child;
            }
            if (child != nullptr)
                child->parent = chosen->parent;
            child -> color = 0;
            delete chosen;
            return;
    }
    deletingFix(chosen);
    if (chosen -> parent -> left == chosen)
        chosen -> parent -> left = nil;
    else
        chosen -> parent -> right = nil;
    delete chosen;
    root -> color = false;
    return;
}
