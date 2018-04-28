#include <iostream>
#include <vector>
#include "RBT.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void visit(RBTNode* x) {
    cout << "key: " << x->key << "\tcolor: " << (x->color ? "RED" : "BLACK") << endl;
}

int main() {
    int k;
    RBT rbt;
    vector<int> ivec{1, 3, 5, 2, 4, 7, 8, 6};
    for (int i = 0; i < ivec.size(); ++i)
        rbt.insert(ivec[i], i);
//    for (int i = 0; cin >> k; ++i) {
//        rbt.insert(k, i);
//    }
    rbt.inorder_walk(visit);
    rbt.remove(2);
    rbt.remove(7);
    rbt.remove(8);
    cout << endl;
    rbt.inorder_walk(visit);
    rbt.remove(5);
    cout << endl;
    rbt.inorder_walk(visit);
    rbt.remove(4);
    cout << endl;
    rbt.inorder_walk(visit);
    rbt.remove(6);
    cout << endl;
    rbt.inorder_walk(visit);
    return 0;
}