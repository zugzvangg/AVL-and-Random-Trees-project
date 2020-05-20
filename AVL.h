
#ifndef AVL_TREE_AVL_H
#define AVL_TREE_AVL_H
#include <iostream>
#include "AVL_Node.h"
#include <vector>
#include <algorithm>
using namespace std;
class AVL{
private:
    Node *head;
    unsigned int size;
public:
    AVL(const int first){head=new Node(first); size=1;}; //init with first key
    AVL(){head=nullptr;size=0;}; //empty init
    ~AVL(){head=delete_n (head);}; //destructor
    Node* show_data(){return head;};
    //controlling tree keys
    void insert(const int a){//inserting num
        head=AVL_TREE_NODE_H::insert(head,a);
        size++;
    }
    void insert(const vector<int> a){//inserting mass
        for(unsigned int i=0;i<a.size();++i) {
            head = AVL_TREE_NODE_H::insert(head, a[i]);
        }
        size+=a.size();
    }
    void remove_element(const int a){//removing num
        head = AVL_TREE_NODE_H::remove(head,a);
        size--;
    }
    void remove_element(const vector<int> a){//removing mass
        for(unsigned int i=0;i<a.size();++i) {
            head = AVL_TREE_NODE_H::remove(head, a[i]);
        }
        size-=a.size();
    }
    unsigned int amount(){
        return size;
    };
    AVL &operator =(const AVL& a){
        this->head=a.head;
        this->size=a.size;
        return *this;
    }
    AVL operator -(const int b){ //subtracting num
        AVL a;
        head = AVL_TREE_NODE_H::remove(head,b);
        a=*this;
        return a;
    };
    AVL operator +(const int b){ //subtracting num
        AVL a;
        head = AVL_TREE_NODE_H::insert(head,b);
        a=*this;
        return a;
    };
};

ostream& operator<<(ostream& os,AVL& a){
    if(a.show_data()==nullptr)
    {
        os<< "empty";
        return os;
    }
    os<<*a.show_data();
    return os;
};
#endif //AVL_TREE_AVL_H
