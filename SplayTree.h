//
// Created by Dell G-3 on 16.10.2019.
//

#ifndef TREESDRAWER_SPLAYTREE_H
#define TREESDRAWER_SPLAYTREE_H


class SplayNode{
public:
    int value;
    SplayNode *left, *right;
};

SplayNode* newNode(int number){
    auto temp = new SplayNode;
    temp -> value = number;
    temp -> left = temp -> right = nullptr;
    return temp;
}

SplayNode *Zag(SplayNode *root)
{
    SplayNode *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}

SplayNode *Zig(SplayNode *root){
    SplayNode *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}

SplayNode *Splay(SplayNode *root, int number){
    if (root == nullptr || root->value == number)
        return root;
    if (root->value > number){
        if (root->left == nullptr)
            return root;
        if (root->left->value > number){
            root->left->left = Splay(root->left->left, number);
            root = Zag(root);
        }
        else if (root->left->value < number){
            root->left->right = Splay(root->left->right, number);
            if (root->left->right != nullptr)
                root->left = Zig(root->left);
        }
        if (root->left == nullptr)
            return root;
        else return Zag(root);
    }
    else {
        if (root->right == nullptr)
            return root;
        if (root->right->value > number){
            root->right->left = Splay(root->right->left, number);
            if (root->right->left != nullptr)
                root->right = Zag(root->right);
        }
        else if (root->right->value < number){
            root->right->right = Splay(root->right->right, number);
            root = Zig(root);
        }
        if (root->right == nullptr)
            return root;
        else return Zig(root);
    }
}

SplayNode *Search(SplayNode *root, int number)
{
    return Splay(root, number);
}

SplayNode *Insert(SplayNode *root, int number){
    if (root == nullptr)
        return newNode(number);
    root = Splay(root, number);
    if (root->value == number)
        return root;
    SplayNode *newnode = newNode(number);
    if (root->value > number){
        newnode->right = root;
        newnode->left = root->left;
        root->left = nullptr;
    }
    else{
        newnode->left = root;
        newnode->right = root->right;
        root->right = nullptr;
    }
    return newnode;
}

SplayNode *Delete(SplayNode *root, int number){
    SplayNode *temp;
    if (root == nullptr)
        return root;
    root = Splay(root, number);
    if (number != root->value)
        return root;
    if (root->left == nullptr){
        temp = root;
        root = root->right;
    }
    else{
        temp = root;
        root = Splay(root->right, number);
        root->right = temp->right;
    }
    delete temp;
    return root;
}


#endif //TREESDRAWER_SPLAYTREE_H
