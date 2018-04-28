//
// Created by qiuyu on 18-4-27.
//

#ifndef RBT_CLION_RBT_H
#define RBT_CLION_RBT_H

typedef int T;
struct RBTNode;

#define RED true
#define BLACK false

typedef void visit_t(RBTNode* node);

//操作接口
bool isRED(RBTNode* x);
bool color(RBTNode* x);
void inorder_tree_walk(RBTNode* node, visit_t visit);
RBTNode* minimum(RBTNode* x);
RBTNode* parent(RBTNode* x);
RBTNode* grand(RBTNode* x);
RBTNode* luncle(RBTNode* lu);
RBTNode* runcle(RBTNode* ru);

struct RBTNode {
public:
    T key;
    T value;
    RBTNode* p;
    RBTNode* lc;
    RBTNode* rc;
    bool color;
    //构造函数
    RBTNode():
            p(nullptr), lc(nullptr), rc(nullptr), color(BLACK), key(-1), value(-1) {}
    RBTNode(T k, T v, bool color = BLACK, RBTNode* p = nullptr, RBTNode* lc = nullptr, RBTNode* rc = nullptr):
            key(k), value(v), color(color), p(p), lc(lc), rc(rc) {}
};



class RBT {
public:
    RBTNode* root;
    RBT(): root(nullptr) {}
    void insert(T key, T value=-1);
    void remove(T key);
    void transplant(RBTNode* origin, RBTNode* follow);
    void inorder_walk(visit_t visit);
private:
    void solveDoubleRed(RBTNode* x);
    void solveDoubleBlack(RBTNode* x, RBTNode* y);
    RBTNode* rotateLeft(RBTNode* origin);
    RBTNode* rotateRight(RBTNode* origin);
};

#endif //RBT_CLION_RBT_H
