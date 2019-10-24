#include <utility>
#include <iostream>

struct SplayTreeNode{
    SplayTreeNode * l = nullptr;
    SplayTreeNode * r = nullptr;
    SplayTreeNode * p = nullptr;
    int val;
    SplayTreeNode():l(nullptr), r(nullptr), p(nullptr), val(0){}
    SplayTreeNode(int x):l(nullptr), r(nullptr), p(nullptr), val(x){}

    ~SplayTreeNode(){
        if (l)
            delete l;
        if (r)
            delete r;
    }
};

class splayTree{
public:
    splayTree():root(nullptr){};
    SplayTreeNode * root = nullptr;

    inline void setParent(SplayTreeNode * child, SplayTreeNode * parent){
        if (child != nullptr)
            child -> p = parent;
    }

    inline void restoreParent(SplayTreeNode * v){
        if (v == nullptr)
            return;
        setParent(v -> l, v);
        setParent(v -> r, v);
    }

    void rotate(SplayTreeNode * parent, SplayTreeNode * child){
        SplayTreeNode * gp = parent -> p;
        if (gp != nullptr)
            if (gp -> l == parent)
                gp -> l = child;
            else
                gp -> r = child;

        if (parent -> l == child){
            parent -> l = child -> r;
            child -> r = parent;
        } else{
            parent -> r = child -> l;
            child -> l = parent;
        }

        restoreParent(child);
        restoreParent(parent);
        child -> p = gp;
    }

    SplayTreeNode * splay (SplayTreeNode * v){
        if (v -> p == nullptr)
            return v;
        SplayTreeNode * p = v -> p;
        SplayTreeNode * gp = p -> p;
        if (gp == nullptr) {
            rotate(p, v);
            return v;
        }

        bool zigzig = (gp -> l == p) == (p -> l == v);

        if (zigzig){
            rotate(gp, p);
            rotate(p, v);
        } else{
            rotate(p, v);
            rotate(gp, v);
        }
        return splay(v);
    }

    SplayTreeNode * find(SplayTreeNode * v, int val){
        if (v == nullptr)
            return nullptr;
        if (v -> val == val)
            return splay(v);
        if (val < v -> val && v -> l != nullptr)
            return find(v -> l, val);
        if (val > v -> val && v -> r != nullptr)
            return find(v -> r, val);
        return splay(v);
    }

    std::pair<SplayTreeNode *, SplayTreeNode *> split(SplayTreeNode * rt, int val){
        if (rt == nullptr)
            return {nullptr, nullptr};
        rt = find(rt, val);
        if (rt -> val == val){
            std::pair<SplayTreeNode *, SplayTreeNode *> ans = {rt -> l, rt -> r};
            setParent(rt -> l, nullptr);
            setParent(rt -> r, nullptr);
            rt -> l = rt -> r = nullptr;
            delete rt;
            return ans;
        }
        if (rt -> val < val){
            SplayTreeNode * r = rt -> r;
            setParent(r, nullptr);
            rt -> r = nullptr;
            return {rt, r};
        }

        SplayTreeNode * l = rt -> l;
        rt -> l = nullptr;
        setParent(l, nullptr);
        return {l, rt};
    }

    SplayTreeNode * insert(SplayTreeNode * rt, int val){
        std::pair<SplayTreeNode *, SplayTreeNode *> res = split(rt, val);
        rt = new SplayTreeNode(val);
        rt -> l = res.first;
        rt -> r = res.second;
        restoreParent(rt);
        return rt;
    }

    SplayTreeNode * merge(SplayTreeNode * left, SplayTreeNode * right){
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;
        right = find(right, left->val);
        right -> l = left;
        left -> p = right;
        return right;
    }

    SplayTreeNode * erase(SplayTreeNode * v, int val){
        SplayTreeNode * rt = find(root, val);
        if (rt == nullptr || rt -> val != val)
            return rt;
        setParent(rt -> l, nullptr);
        setParent(rt -> r, nullptr);
        std::pair <SplayTreeNode *, SplayTreeNode *> ans = {rt -> l, rt -> r};
        rt -> l = rt -> r = nullptr;
                delete rt;
        return merge(ans.first, ans.second);
    }

    SplayTreeNode * erase(int val){
        root = erase(root, val);
    }



    void print(SplayTreeNode * rt){
        if (rt == nullptr)
            return;
        print(rt -> l);
        std::cout << rt -> val << ' ';
        print(rt -> r);
    }

public:
    void insert(int val){
        root = insert(root, val);
    }

    void print(){
        print(root);
    }
};
