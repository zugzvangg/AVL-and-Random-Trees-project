//definition NODE_AVL
#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H
//initial libs
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
using namespace std;
//Node body
template <typename T>
struct Node {
    //main items
    T key;
    Node<T>* l=nullptr, *r=nullptr;
    unsigned int height;
    int s;
    //basic init
    Node(T key) { this->key = key;
                l = nullptr;
                r = nullptr;
                height = 1;
    };
    //destructor
    ~Node(){};
};
//info funcs
template <typename T> bool search(Node<T>* a, T b);   //looking for element
template <typename T> unsigned int get_height(Node<T>* a);        //finding out height of tree
template <typename T> int difference(Node<T>*a);                  //finding out the difference between tree branches
template <typename T> Node<T>* find_min(Node<T>* a);              //looking for the minimal key
//fixing funcs
template <typename T> void fix_height(Node<T>& a);                //fixing height
//rotation funcs
template <typename T> Node<T>* rotate_r(Node<T> *a);              //small r rotation
template <typename T> Node<T>* rotate_l(Node<T> *a);              //small l rotation
template <typename T> Node<T>* big_rotate_r(Node<T>* a);          //big r rotation
template <typename T> Node<T>* big_rotate_l(Node<T>* a);          //big l rotation
//balancing node
template <typename T> Node<T>* balance(Node<T>* a);
//formatting funcs
template <typename T> Node<T>* remove_min(Node<T>* a);            //deleting minimal
template <typename T> Node<T>* insert(Node<T>* a, T b);   //adding element
template <typename T> Node<T>* remove(Node<T>* a, T b);   //deleting element


//realisation
//info funcs
template <typename T> bool search(Node<T>* a, const T b){
    if(a==nullptr){
        return false;
    }
    if(b<a->key){
        return search(a->l, b);
    }
    else if(b>a->key){
        return search(a->r,b);
    }
    return true;
}  //looking for element
template <typename T> unsigned int get_height(Node<T>* a){
    if(a==nullptr){
        return 0;
    }
    return a->height;
}       //finding out height of tree
template <typename T> int difference(Node<T>*a){
    if(a==nullptr){
        return 0;
    }
    return((get_height(a->r))-(get_height(a->l)));
}        //finding out the difference between tree branches
template <typename T> Node<T>* find_min(Node<T>* a){
    if(a==nullptr){
        return a;
    }
    if(a->l==nullptr){
        return a;
    } else
        return find_min(a->l);
}             //looking for the minimal key
//fixing funcs
template <typename T> void fix_height(Node<T>& a){
    if(get_height(a.r)>get_height(a.l)){
        a.height=get_height(a.r)+1;
    }else {
        a.height = get_height(a.l) + 1;
    }
}               //fixing height
//rotation funcs
template <typename T> Node<T>* rotate_r(Node<T> *a){
    Node<T>*c=a;
    Node<T>*b=c->l;
    a->l=b->r;
    b->r=c;
    fix_height(*c);
    fix_height(*b);
    return b;
}             //small r rotation
template <typename T> Node<T>* rotate_l(Node<T> *a){
    Node<T>*c=a;
    Node<T>*b=c->r;
    c->r = b->l;
    b->l = c;
    fix_height(*c);
    fix_height(*b);
    return b;
}             //small l rotation
template <typename T> Node<T>* big_rotate_r(Node<T>* a){
    a->l=rotate_l(a->l);
    return rotate_r(a);
}         //big r rotation
template <typename T> Node<T>* big_rotate_l(Node<T>* a){
    a->r=rotate_r(a->r);
    return rotate_l(a);
}         //big l rotation
//balancing node
template <typename T> Node<T>* balance(Node<T>* a){
    fix_height(*a);
    if(difference(a)==2){
        if(difference(a->r)<0){
            a=big_rotate_l(a);}
        else{a=rotate_l(a);}
    }
    if(difference(a)==-2){
        if(difference(a->l)>0){
            a= big_rotate_r(a);}
        else{a=rotate_r(a);}
    }
    return a;
}
//formatting funcs
template <typename T> Node<T>* remove_min(Node<T>* a){
    if(a==nullptr){
        throw runtime_error("Can't delete minimal from empty tree!");
    }
    if(a->l==nullptr){
        return a->r;
    }
    a->l=remove_min(a->l);
    return balance(a);
}           //deleting minimal
template <typename T> Node<T>* insert(Node<T>* a, const T b){
    if(a==nullptr){
        a=new Node<T>(b);
        return a;
    }
    if(b<a->key){
        a->l=insert(a->l,b);
    }
    else{
        a->r=insert(a->r,b);
    }
    return a=balance(a);
}  //adding element
template <typename T> Node<T>* remove(Node<T>* a, const T b){
    if(a==nullptr){
        return nullptr;
    }
    if(b<a->key){
        a->l=remove(a->l, b);
    }
    else if(b>a->key){
        a->r=remove(a->r,b);
    }
    else{
        Node<T>* l = a->l;
        Node<T>* r = a->r;
        Node<T>*min= find_min(a);
        delete a;
        if(r==nullptr){
            a=l;
        }
        a=find_min(r);
        if(a!=nullptr) {
            r=remove_min(r);
            a->r=r;
            a->l=l;
            a = balance(a);
            return a;
        }
        return nullptr;
    }
    a = balance(a);
    return a;
}  //deleting element
//operator
template <typename T> ostream &operator<<(ostream& os, Node<T>& node) //output
{
    if (node.l)
        os << *(node.l);
    os << (node.key) << endl;
    if (node.r)
        os << *(node.r);

    return os;
}
/**
struct Node {
    //main items
    int key;
    Node *l, *r;
    unsigned int height;
    Node(int key) { this->key = key; l = nullptr; r = nullptr; height = 1; };
    Node* copy_tree(Node* a){//copying tree
        if(a==nullptr)return nullptr;
        Node*b = new Node(a->key);
        b->l=copy_tree(a->l);
        b->r=copy_tree(a->r);
        return b;
    };
    Node(const Node &a){this->key=a.key;this->l=copy_tree(a.l);this->r=copy_tree(a.r);this->height=a.height;};
    ~Node(){};
};
//
//Finding out Node info
bool const search(Node* a, const int b){
    if(a==nullptr){
        return false;
    }
    if(b<a->key){
        return search(a->l, b);
    }
    else if(b>a->key){
        return search(a->r,b);
    }
    return true;
}
unsigned int get_height(Node* a){
    if(a==nullptr){
        return 0;
    }
    return a->height;
}
unsigned int difference(Node *a){
    if(a==nullptr){
        throw runtime_error("Non empty pointer is required!");
    }
    return(get_height(a->r)-get_height(a->l));
}
Node* find_min(Node* a){ //searching the minimal element
    if(a==nullptr){
        return a;
    }
    if(a->l==nullptr){
        return a;
    } else
        return find_min(a->l);
}
//Fixing Node
void fix_height(Node& a){
    if(get_height(a.r)>get_height(a.l)){
        a.height=get_height(a.r)+1;
    }else {
        a.height = get_height(a.l) + 1;
    }
}
//Node rotations
Node* rotate_r(Node *a){ //small r rotation
    Node*c=a;
    Node *b=c->l;
    a->l=b->r;
    b->r=c;
    fix_height(*c);
    fix_height(*b);
    return b;
}
Node* rotate_l(Node *a){ //small l rotation
    Node*c=a;
    Node *b=c->r;
    c->r=b->l;
    b->l=c;
    fix_height(*c);
    fix_height(*b);
    return b;
}
Node* big_rotate_r(Node* a){ //big r rotation
    a->l=rotate_l(a->l);
    return rotate_r(a);
}
Node* big_rotate_l(Node* a){ //big l rotation
    a->r=rotate_r(a->r);
    return rotate_l(a);
}
//balancing node
Node* balance(Node* a){
    fix_height(*a);
    if(difference(a)==2){
        if(difference(a->r)<0){
        a=big_rotate_l(a);}else{a=rotate_l(a);}
    }
    if(difference(a)==-2){
        if(difference(a->l)>0){
           a= big_rotate_r(a);}else{a=rotate_r(a);}
    }
    return a;
}
//Node formatting
Node* remove_min(Node* a){ //deleting minimal
    if(a==nullptr){
        throw runtime_error("Can't delete minimal from empty tree!");
    }
    if(a->l==nullptr){
        return a->r;
    }
    a->l=remove_min(a->l);
    return balance(a);
}
Node* insert(Node* a, const int b){ //adding element
    if(a==nullptr){
        return new Node(b);
    }
    if(b<a->key){
        a->l=insert(a->l,b);
    }
    else{
        a->r=insert(a->r,b);
    }
    return a=balance(a);
}
Node* remove(Node* a, const int b){//deleting element
    if(a==nullptr){
        return nullptr;
    }
    if(b<a->key){
        a->l=remove(a->l, b);
    }
    else if(b>a->key){
        a->r=remove(a->r,b);
    }
    else{
        Node* l = a->l;
        Node* r = a->r;
        Node *min= find_min(a);
        delete a;
        if(r==nullptr){
            a=l;
        }
        a=find_min(r);
        if(a!=nullptr) {
            r=remove_min(r);
            a->r=r;
            a->l=l;
            a = balance(a);
            return a;
        }
        return nullptr;
    }
   a = balance(a);
    return a;
}
//destructor
void del(Node*& a){
   if(a!=nullptr){
       del(a->l);
       del(a->r);
       delete a;
       a=nullptr;
   }
}
//operators
ostream& operator<<(ostream &os, const Node& a){
    Node* b=new Node(a);
    Node* i;
    while(b->l!=nullptr){
       i=find_min(b->l);
       cout<< "| "<< i->key <<" | ";
       b->l=remove_min(b->l);
    }
    cout<<"( "<<b->key<<" )";
    while(b->r!=nullptr){
        i=find_min(b->r);
        cout<< " | "<< i->key <<" |";
        b->r=remove_min(b->r);
    }
    delete b,i;
    return os;
}
 **/
#endif