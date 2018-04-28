//
// Created by qiuyu on 18-4-27.
//
#include "RBT.h"

void inorder_tree_walk(RBTNode *node, visit_t visit) {
    if (node) {
        inorder_tree_walk(node->lc, visit);
        visit(node);
        inorder_tree_walk(node->rc, visit);
    }
}

RBTNode* RBT::rotateLeft(RBTNode *origin) {
    RBTNode* follow = origin->rc;
    origin->rc = follow->lc;
    if (follow->lc)
        follow->lc->p = origin;

    follow->p = origin->p;
    if (origin->p == nullptr)
        this->root = follow;
    else if (origin == parent(origin)->lc)
        parent(origin)->lc = follow;
    else
        parent(origin)->rc = follow;

    follow->lc = origin;
    origin->p = follow;
    bool follow_color = follow->color;
    follow->color = origin->color;
    origin->color = follow_color;
    return follow;
}

RBTNode* RBT::rotateRight(RBTNode *origin) {
    RBTNode* follow = origin->lc;
    origin->lc = follow->rc;
    if (follow->rc)
        follow->rc->p = origin;

    follow->p = origin->p;
    if (origin->p == nullptr)
        this->root = follow;
    else if (origin == parent(origin)->lc)
        parent(origin)->lc = follow;
    else
        parent(origin)->rc = follow;

    follow->rc = origin;
    origin->p = follow;
    bool  follow_color = follow->color;
    follow->color = origin->color;
    origin->color = follow_color;
    return follow;
}

bool isRED(RBTNode *x) {
    if (x)
        return x->color == RED ? RED : BLACK;
    return BLACK;
}

bool col(RBTNode* x) {
    return isRED(x);
}

RBTNode* parent(RBTNode* x) {
    if (x)
        return x->p;
    return nullptr;
}

RBTNode* grand(RBTNode* x) {
    if (parent(x))
        return parent(x)->p;
    return nullptr;
}

RBTNode* luncle(RBTNode* x) {
    if (grand(x))
        return grand(x)->lc;
    return nullptr;
}

RBTNode* runcle(RBTNode* x) {
    if (grand(x))
        return grand(x)->rc;
    return nullptr;
}


void RBT::insert(T key, T value) {
    RBTNode* y = nullptr;
    RBTNode* x = this->root;
    while (x) {
        y = x;
        if (key < x->key)
            x = x->lc;
        else if (x->key < key)
            x = x->rc;
        else
            return ;
    }
    RBTNode *z = new RBTNode(key, value, RED);
    z->p = y;
    if (y == nullptr)
        this->root = z;
    else if (z->key < y->key)
        y->lc = z;
    else
        y->rc = z;
    solveDoubleRed(z);
}

void RBT::solveDoubleRed(RBTNode *x) {
    while (isRED(parent(x))) {
        if (parent(x) == grand(x)->lc) {     //左侧情况
            if (isRED(runcle(x))) {     //case 1
                grand(x)->color = RED;
                parent(x)->color = BLACK;
                runcle(x)->color = BLACK;
                x= grand(x);
            } else if (x == parent(x)->rc) {    //case 2
                x = x->p;
                rotateLeft(x);
            } else if (x == parent(x)->lc) {
                rotateRight(grand(x));       //case 3
            }
        } else {                //右侧情况
            if (isRED(luncle(x))) {     //case 1
                grand(x)->color = RED;
                parent(x)->color = BLACK;
                luncle(x)->color = BLACK;
                x = grand(x);
            } else if (x == parent(x)->lc) {     //case 2
                x = x->p;
                rotateRight(x);
            } else if (x == parent(x)->rc) {
                rotateLeft(grand(x));       //case 3
            }
        }
    }
    this->root->color = BLACK;
}

/*
void RBT::solveDoubleRed(RBTNode *x) {
    while (isRED(x->p)) {
        if (x->p == x->p->p->lc) {     //左侧情况
            if (isRED(x->p->p->rc)) {     //case 1
                x->p->p->color = RED;
                x->p->color = BLACK;
                x->p->p->rc->color = BLACK;
                x= x->p->p;
            } else if (x == x->p->rc) {    //case 2
                x = x->p;
                rotateLeft(x);
            } else if (x == x->p->rc) {
                rotateRight(x->p->p);       //case 3
            }
        } else {                //右侧情况
            if (isRED(x->p->p->lc)) {     //case 1
                x->p->p->color = RED;
                x->p->color = BLACK;
                x->p->p->lc->color = BLACK;
                x = x->p->p;
            } else if (x == x->p->lc) {     //case 2
                x = x->p;
                rotateRight(x);
            } else if (x == x->p->rc) {
                rotateLeft(x->p->p);       //case 3
            }
        }
    }
    this->root->color = BLACK;
}
*/

void RBT::transplant(RBTNode *origin, RBTNode *follow) {
    if (origin->p == nullptr)
        this->root = follow;
    else if (origin == parent(origin)->lc)
        parent(origin)->lc = follow;
    else
        parent(origin)->rc = follow;
    if (follow) {
        follow->p = origin->p;
//        follow->color = origin->color;
    }
}

RBTNode* search(RBTNode* x, T key) {
    while (x) {
        if (key < x->key)
            x = x->lc;
        else if (x->key < key)
            x = x->rc;
        else
            return x;
    }
    return x;
}

RBTNode* minimum(RBTNode* x) {
    while (x->lc)
        x = x->lc;
    return x;
}

void RBT::remove(T key) {
    RBTNode* z = search(this->root, key);
    if (z == nullptr)
        return ;
    RBTNode* y = z;
    RBTNode* x = nullptr;
    RBTNode* parent_x = nullptr;
    bool origin_color = y->color;
    if (z->lc == nullptr) {
        x = z->rc;
        parent_x = z->p;
        transplant(z, z->rc);
    } else if (z->rc == nullptr) {
        x = z->lc;
        parent_x = z->p;
        transplant(z, z->lc);
    } else {
        y = minimum(z->rc);
        origin_color = y->color;
        x = y->rc;
        if (y->p == z) {
            parent_x = y;
            if (x)
                x->p = y;
        }
        else {
            parent_x = y->p;
            transplant(y, y->rc);
            y->rc = z->rc;
            y->rc->p = y;
        }
        transplant(z, y);
        y->lc = z->lc;
        y->lc->p = y;
        y->color = z->color;
    }
    if (origin_color == BLACK)
        solveDoubleBlack(x, parent_x);
}

void RBT::solveDoubleBlack(RBTNode *x, RBTNode* y) {
    while (x != this->root &&  col(x) == BLACK) {
        RBTNode* p = (x == nullptr ? y : parent(x));
        if (x == p->lc) {
            RBTNode* w = p->rc;
            if (col(w) == RED) {      //case 1
                rotateLeft(p);
                w = p->rc;
            }
            if (col(w->lc) == BLACK && col(w->rc) == BLACK) {   //case 2
                w->color = RED;
                x = p;
            } else if (col(w->rc) == BLACK) {    //case 3
                w = rotateRight(w);
            } else if (col(w->rc) == RED) {
                w->rc->color = BLACK;               //case 4
                rotateLeft(p);
                x = this->root;
            }
        } else {
            RBTNode* w = p->lc;
            if (col(w) == RED) {      //case 1
                rotateRight(p);
                w = p->lc;
            }
            if (col(w->lc) == BLACK && col(w->rc) == BLACK) {   //case 2
                w->color = RED;
                x = p;
            } else if (col(w->lc) == BLACK) {   //case 3
                w = rotateLeft(w);
            } else if (col(w->lc) == RED) {
                w->lc->color = BLACK;           //case 4
                rotateRight(parent(x));
                x = this->root;
            }
        }
    }
    if (x)
        x->color = BLACK;
}

/*
void RBT::solveDoubleBlack(RBTNode *x, RBTNode* y) {
    while (x != this->root && x->color == BLACK) {
        if (x == parent(x)->lc) {
            RBTNode* w = parent(x)->rc;
            if (w->color == RED) {      //case 1
                rotateLeft(parent(x));
                w = parent(x)->rc;
            }
            if (w->lc->color == BLACK && w->rc->color == BLACK) {   //case 2
                w->color = RED;
                x = parent(x);
            } else if (w->lc->color == RED) {    //case 3
                w = rotateRight(w);
            }
            w->rc->color = BLACK;               //case 4
            rotateLeft(parent(x));
            x = this->root;
        } else {
            RBTNode* w = parent(x)->lc;
            if (w->color == RED) {      //case 1
                rotateRight(parent(x));
                w = parent(x)->lc;
            }
            if (w->lc->color == BLACK && w->rc->color == BLACK) {   //case 2
                w->color = RED;
                x = parent(x);
            } else if (w->rc->color == RED) {   //case 3
                w = rotateLeft(w);
            }
            w->lc->color = BLACK;
            rotateRight(parent(x));
            x = this->root;
        }
    }
    this->root->color = BLACK;
}
*/


void RBT::inorder_walk(visit_t visit) {
    inorder_tree_walk(this->root, visit);
}
