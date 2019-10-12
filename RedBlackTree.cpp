//
// Created by Dell G-3 on 07.10.2019.
//

#include "RedBlackTree.h"

//Local functions

bool isRed(RedBlackTreeNode::Node* node) {
    if (node == nullptr) return 0;
    return (!node -> black);
}

bool isLeft(RedBlackTreeNode::Node *node) {
    return (node->father != nullptr && node -> father -> left == node);
}

void rotateLeft(RedBlackTreeNode::Node *root) {
    RedBlackTreeNode::Node *tmp = root -> right;
    tmp -> father = root -> father;
    if (root -> father != nullptr) {
        if (root -> father -> left == root)
            root -> father -> left = tmp;
        else
            root -> father -> right = tmp;
    }
    root -> father = tmp;
    root -> right = tmp -> left;
    if (root -> right != nullptr)
        root -> right -> father = root;
    tmp -> left = root;
    return;
}
void rotateRight(RedBlackTreeNode::Node *root) {
    RedBlackTreeNode::Node *tmp = root -> left;
    tmp -> father = root -> father;
    if (root -> father != nullptr) {
        if (root -> father -> left == root)
            root -> father -> left = tmp;
        else
            root -> father -> right = tmp;
    }
    root -> father = tmp;
    root -> left = tmp -> right;
    if (root -> left != nullptr)
        root -> left -> father = root;
    tmp -> right = root;
    return;
}
//Global functions

RedBlackTreeNode::Node* RedBlackTree::search(int key) {
    RedBlackTreeNode::Node *tmp= root;
    while (tmp != nullptr && tmp -> value != key) {
        if (tmp -> value < key)
            tmp = tmp -> right;
        else
            tmp = tmp -> left;
    }
    return tmp;
}

RedBlackTreeNode::Node::Node(int key, bool color, RedBlackTreeNode::Node * l, RedBlackTreeNode::Node * r) {
    value = key;
    black = color;
    left = l;
    right = r;
    father = nullptr;
}

void RedBlackTree::insert(int key) {
    RedBlackTreeNode::Node *insertingElement = new RedBlackTreeNode::Node(key, 0, nullptr, nullptr);
    if (root == nullptr) {
        root = insertingElement;
        root ->black = true;
        return;
    } else {
        RedBlackTreeNode::Node *iterator1 = root, *iterator2 = nullptr;
        while (iterator1 != nullptr) {
            iterator2 =iterator1;
            if (iterator1->value < insertingElement -> value)
                iterator1 = iterator1 -> right;
            else
                iterator1 = iterator1 -> left;
        }
        insertingElement -> father = iterator2;
        if (iterator2->value < insertingElement -> value)
            iterator2 -> right = insertingElement;
        else
            iterator2 -> left = insertingElement;
    }
    RedBlackTreeNode::Node* iterator = insertingElement, *uncle;
    while (isRed(iterator -> father)) {
        if (isLeft(iterator -> father)) {
            uncle = iterator -> father -> father -> right;
            if (isRed(uncle)) {
                iterator -> father -> black = true;
                uncle -> black = true;
                uncle -> father -> black = false;
            } else {
                if (isLeft(iterator)) {
                    iterator  = iterator -> father;
                } else {
                    rotateLeft(iterator -> father);
                }
                iterator -> black = true;
                iterator -> father -> black = false;
                rotateRight(iterator -> father);
            }
        } else {
            uncle = iterator -> father -> father -> left;
            if (isRed(uncle)) {
                iterator -> father -> black = true;
                uncle -> black = true;
                uncle -> father -> black = false;
            } else {
                if (!isLeft(iterator)) {
                    iterator  = iterator -> father;
                } else {
                    rotateRight(iterator -> father);
                }
                rotateLeft(iterator -> father);
            }
        }
    }

}


RedBlackTreeNode::Node* treeSuccessor(RedBlackTreeNode::Node *x){
    if(x->right != nullptr){
        x = x->right;
        while( x->left != nullptr)
            x = x->left;
        return x;
    }
    _rbTreeNode<T> * y = x->p;
    while( y != nil && x == y->right ){
        x = y;
        y = y->p;
    }
    return y;
}

void RedBlackTree::erase( _rbTreeNode<T> *z ){
    _rbTreeNode<T> * x = nil;
    _rbTreeNode<T> * y = nil;
    if( z->left == nil || z->right == nil )
        y = z;
    else
        y = treeSuccessor( z );
    if( y->left != nil )
        x = y->left;
    else
        x = y->right;
    x->p = y->p;
    if( y->p == nil )
        root = x;
    else{
        if( y == y->p->left )
            y->p->left = x;
        else
            y->p->right = x;
    }
    if( y != z )
        z->key = y->key;
    if( y->color == false )
        rbDeleteFixup( x );
    delete y;
}

template <class T>
void rbtree<T>::rbDeleteFixup(_rbTreeNode<T> * x){
    while( x != root && x->color == false ){
        _rbTreeNode<T> * w = 0;
        if( x->p->left == x ){
            w = x->p->right;
            if( w->color == true ){
                w->color = false;
                x->p->color = true;
                leftRotate( x->p );
                w = x->p->right;
            }
            if( w->left->color == false && w->right->color == false ){
                w->color = true;
                x = x->p;
            }
            else{
                if( w->right->color == false ){
                    w->left->color = false;
                    w->color = true;
                    rightRotate( w );
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = false;
                w->right->color = false;
                leftRotate( x->p );
                x = root;
            }
        }
        else{
            w = x->p->left;
            if( w->color == true ){
                w->color = false;
                x->p->color = true;
                rightRotate( x->p );
                w = x->p->left;
            }
            if( w->right->color == false && w->left->color == false ){
                w->color = true;
                x = x->p;
            }
            else{
                if( w->left->color == false ){
                    w->right->color = false;
                    w->color = true;
                    leftRotate( w );
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = false;
                w->left->color = false;
                rightRotate( x->p );
                x = root;
            }
        }
    }
    x->color = false;
}

//void  RedBlackTree::erase(int key) {
//    RedBlackTreeNode::Node *tmp = root;
//
//    if (root -> value == key) {
//        if (root -> right == 0) {
//            root -> left =
//        }
//    }
//
//    while (tmp -> value != key) {
//        if (tmp -> value < key)
//            tmp = tmp -> right;
//        else
//            tmp = tmp -> left;
//    }
//    if (tmp ->right == nullptr && tmp -> left == nullptr) {
//        if (tmp -> father -> right == tmp)
//            tmp -> father -> right = nullptr;
//        else
//            tmp -> father -> left = nullptr;
//        delete tmp;
//        return;
//    }
//    RedBlackTreeNode::Node *tmp2 = nullptr;
//    if (tmp -> right == nullptr)
//        tmp2 = tmp -> left;
//    if (tmp -> left == nullptr)
//        tmp2 = tmp -> right;
//    if (tmp2 != nullptr) {
//        if (tmp -> father -> right == tmp)
//            tmp -> father -> right = tmp2;
//        else
//            tmp -> father -> left = tmp2;
//        delete tmp;
//        return;
//    }
//
//
//}