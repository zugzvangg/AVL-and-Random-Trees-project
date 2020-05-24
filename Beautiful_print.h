
#ifndef UNTITLED1_BEAUTIFUL_PRINT_H
#define UNTITLED1_BEAUTIFUL_PRINT_H
#include "Timer.h"
#include <fstream>
#include "AVL_Node.h"
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <assert.h>
using namespace std;

struct Node_print_state {
    Node_print_state* Child_state;
    bool Printing_last_child;
};
Node_print_state* r_s_1 = nullptr;

template<typename T>void Print_subtree(const Node<T>* node);

template <typename T> void print_tree(const Node<T>* root) {
    assert(r_s_1 == nullptr);
    try {
        if (root != nullptr) {
            Print_subtree(root);
        }
    } catch (...) {
        // Exception if something wrong
        r_s_1 = nullptr;
        throw;
    }
}

template<typename T> void Print_subtree(const Node<T>* node) {
    Node_print_state* Parent_state;
    if (r_s_1 != nullptr) {
        cout<<" ";
        Node_print_state* s = r_s_1;
        while (s->Child_state != nullptr) {
            if(s->Printing_last_child){
                cout<<"   ";
            }
            else cout<<"|  ";
            s = s->Child_state;
        }
        Parent_state = s;
        if(Parent_state->Printing_last_child ){
            cout<<"L";
        }
        else cout<<"+";
    } else {
        Parent_state = nullptr;
    }
    cout<<"->"<< node->key<<endl;

    if ((node->l != nullptr) || (node->r != nullptr)) {
        Node_print_state s;
        if (Parent_state != nullptr) {
            Parent_state->Child_state = &s;
        } else {
            r_s_1 = &s;
        }
        s.Child_state = nullptr;

        // печатаем детей
        if (node->l != nullptr) {
            s.Printing_last_child = (node->r == nullptr);
            Print_subtree(node->l);
        }
        if (node->r != nullptr) {
            s.Printing_last_child = true;
            Print_subtree(node->r);
        }

        if (Parent_state != nullptr) {
            Parent_state->Child_state = nullptr;
        } else {
            r_s_1 = nullptr;
        }
    }
}
#endif //BEAUTIFUL_PRINT_H
