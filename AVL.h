//definition TREE_AVL
#ifndef AVL_TREE_AVL_H
#define AVL_TREE_AVL_H
//initial libs
#include "Tree.h"
#include <iostream>
#include "AVL_Node.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
using namespace std;
//Tree body
template <typename T>
class AVL: public Tree<T>{
//tree items
private:
    Node<T> *head;
    unsigned int size;
//
//destruction_func
static void destroy_node(Node<T>* node){
    if(node){
        destroy_node(node->l);
        destroy_node(node->r);
        delete node;
    }
}
//
public:
//constructors
AVL(const int first){head=new Node<T>(first); size=1;}; //init with first key
AVL():head(nullptr),size(0){};                          //empty init
AVL(AVL<T> const& other):head(nullptr){
    vector<Node<T> const*> remaining;
    Node<T> const* cur=other.head;
    while(cur){
        insert(cur->key);
        if(cur->r){
            remaining.push_back(cur->r);
        }
        if(cur->l){
            cur=cur->l;
        }
        else if(remaining.empty()){
            break;
        }
        else{
            cur=remaining.back();
            remaining.pop_back();
        }
    }
};
//destructor
~AVL(){destroy_node(head);}
//methods
//info funcs
Node<T>* const show_data();                         //outputting data
bool const search(const int a);                     //looking for element
unsigned int amount();                              //showing amount of elements
//moderating funcs
void insert(T a);                                   //inserting 1 element
void insert(const vector<T> a);                     //inserting mass of elements
void remove_element(const T a);                     //removing 1 element
void remove_element(const vector<T> a);             //removing mass of elements
void remove_minimal(){
    head=remove_min(head);
};                         //removing minimal
//interface methods;
     T FIND_MIN_ELEMENT();                          //minimal element
     T FIND_MAX_ELEMENT();                          //maximal element
     Node<T>* FIND_NODE(T data);                    //search with key
     void INSERT(T data);                           //insertion
     void DELETE(T data);                           //deleting
};
//methods realising
//moderating funcs
template<typename T> void AVL<T>::insert(const T a){
head=AVL_TREE_NODE_H::insert(head,a);
size++;
}; //inserting 1 element
template<typename T> void AVL<T>::insert(const vector<T> a){
    for(unsigned int i=0;i<a.size();++i) {
        this->insert(a[i]);
    }
};          //inserting mass of elements
template<typename T> void AVL<T>::remove_element(const T a){
    if(::search(head, a)){
        size--;
    }
    head = AVL_TREE_NODE_H::remove(head,a);
};          //removing 1 element
template<typename T> void AVL<T>::remove_element(const vector<T> a){
    for(unsigned int i=0;i<a.size();++i) {
        this->remove_element(a[i]);
    }
};  //removing mass of elements
//info funcs
template<typename T> Node<T>* const AVL<T>::show_data(){
    return head;
};              //outputting data
template<typename T> bool const AVL<T>::search(const int a){
    return AVL_TREE_NODE_H::search(head,a); //is element here?
};          //looking for element
template<typename T> unsigned int AVL<T>::amount(){
    return size;
};                   //showing amount of elements
//operator realisation
//operators
template<typename T> ostream& operator <<(ostream& os,AVL<T>& a){
if(a.show_data())
    os<<*a.show_data();
return os;
};           //output
//interface methods realising
template<typename T> T AVL<T>::FIND_MIN_ELEMENT(){
    Node<T> *current = head;
    while(current->l!= nullptr)
    {
        current=current->l;
    }
    cout << "Minimal element in the tree = " << current->key << endl;
    return current->key;
};                          //minimal element
template<typename T> T AVL<T>::FIND_MAX_ELEMENT(){
    Node<T> *current = head;
    while(current->r!=nullptr)
    {
        current=current->r;
    }
    cout << "Maximal element in the tree = " << current->key << endl;
    return current->key;
};                          //maximal element
template<typename T> Node<T>* AVL<T>::FIND_NODE(T data){
    Node<T> *current = head;
    while (current != nullptr)
        if (data == current->key) {
            cout << "There is an element = " << data << " in the tree"<<endl;
            return (current);
        } else if (data < current->key) {
            current = current->l;
        } else {
            current = current->r;
        }
    cout << "There is no such element"<<endl;
    return nullptr;
};                    //search with key
template<typename T> void AVL<T>::INSERT(T data){
    this->insert(data);
};                           //insertion
template<typename T> void AVL<T>::DELETE(T data){
    this->remove_element(data);
};                           //deleting

#endif //AVL_TREE_AVL_H
