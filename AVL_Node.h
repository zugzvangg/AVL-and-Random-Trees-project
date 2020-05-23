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
    Node<T>* left=nullptr, *right=nullptr;
    unsigned int height;
    //basic init
    Node(T key) { this->key = key;
                left = nullptr;
                right = nullptr;
                height = 1;
    };
    //destructor
    ~Node(){};
};
//info funcs
template <typename T> bool const search(Node<T>* a, const T b);   //looking for element
template <typename T> unsigned int get_height(Node<T>* a);        //finding out height of tree
template <typename T> int difference(Node<T>*a);                  //finding out the difference between tree branches
template <typename T> Node<T>* find_min(Node<T>* a);              //looking for the minimal key
//fixing funcs
template <typename T> void fix_height(Node<T>& a);                //fixing height
//rotation funcs
template <typename T> Node<T>* rotate_r(Node<T> *a);              //small right rotation
template <typename T> Node<T>* rotate_l(Node<T> *a);              //small left rotation
template <typename T> Node<T>* big_rotate_r(Node<T>* a);          //big right rotation
template <typename T> Node<T>* big_rotate_l(Node<T>* a);          //big left rotation
//balancing node
template <typename T> Node<T>* balance(Node<T>* a);
//formatting funcs
template <typename T> Node<T>* remove_min(Node<T>* a);            //deleting minimal
template <typename T> Node<T>* insert(Node<T>* a, const T b);   //adding element
template <typename T> Node<T>* remove(Node<T>* a, const T b);   //deleting element


//realisation
//info funcs
template <typename T> bool const search(Node<T>* a, const T b){
    if(a==nullptr){
        return false;
    }
    if(b<a->key){
        return search(a->left, b);
    }
    else if(b>a->key){
        return search(a->right,b);
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
    return((get_height(a->right))-(get_height(a->left)));
}        //finding out the difference between tree branches
template <typename T> Node<T>* find_min(Node<T>* a){
    if(a==nullptr){
        return a;
    }
    if(a->left==nullptr){
        return a;
    } else
        return find_min(a->left);
}             //looking for the minimal key
//fixing funcs
template <typename T> void fix_height(Node<T>& a){
    if(get_height(a.right)>get_height(a.left)){
        a.height=get_height(a.right)+1;
    }else {
        a.height = get_height(a.left) + 1;
    }
}               //fixing height
//rotation funcs
template <typename T> Node<T>* rotate_r(Node<T> *a){
    Node<T>*c=a;
    Node<T>*b=c->left;
    a->left=b->right;
    b->right=c;
    fix_height(*c);
    fix_height(*b);
    return b;
}             //small right rotation
template <typename T> Node<T>* rotate_l(Node<T> *a){
    Node<T>*c=a;
    Node<T>*b=c->right;
    c->right = b->left;
    b->left = c;
    fix_height(*c);
    fix_height(*b);
    return b;
}             //small left rotation
template <typename T> Node<T>* big_rotate_r(Node<T>* a){
    a->left=rotate_l(a->left);
    return rotate_r(a);
}         //big right rotation
template <typename T> Node<T>* big_rotate_l(Node<T>* a){
    a->right=rotate_r(a->right);
    return rotate_l(a);
}         //big left rotation
//balancing node
template <typename T> Node<T>* balance(Node<T>* a){
    fix_height(*a);
    if(difference(a)==2){
        if(difference(a->right)<0){
            a=big_rotate_l(a);}
        else{a=rotate_l(a);}
    }
    if(difference(a)==-2){
        if(difference(a->left)>0){
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
    if(a->left==nullptr){
        return a->right;
    }
    a->left=remove_min(a->left);
    return balance(a);
}           //deleting minimal
template <typename T> Node<T>* insert(Node<T>* a, const T b){
    if(a==nullptr){
        a=new Node(b);
        return a;
    }
    if(b<a->key){
        a->left=insert(a->left,b);
    }
    else{
        a->right=insert(a->right,b);
    }
    return a=balance(a);
}  //adding element
template <typename T> Node<T>* remove(Node<T>* a, const T b){
    if(a==nullptr){
        return nullptr;
    }
    if(b<a->key){
        a->left=remove(a->left, b);
    }
    else if(b>a->key){
        a->right=remove(a->right,b);
    }
    else{
        Node<T>* left = a->left;
        Node<T>* right = a->right;
        Node<T>*min= find_min(a);
        delete a;
        if(right==nullptr){
            a=left;
        }
        a=find_min(right);
        if(a!=nullptr) {
            right=remove_min(right);
            a->right=right;
            a->left=left;
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
    if (node.left)
        os << *(node.left);
    os << (node.key) << endl;
    if (node.right)
        os << *(node.right);

    return os;
}
/**
struct Node {
    //main items
    int key;
    Node *left, *right;
    unsigned int height;
    Node(int key) { this->key = key; left = nullptr; right = nullptr; height = 1; };
    Node* copy_tree(Node* a){//copying tree
        if(a==nullptr)return nullptr;
        Node*b = new Node(a->key);
        b->left=copy_tree(a->left);
        b->right=copy_tree(a->right);
        return b;
    };
    Node(const Node &a){this->key=a.key;this->left=copy_tree(a.left);this->right=copy_tree(a.right);this->height=a.height;};
    ~Node(){};
};
//
//Finding out Node info
bool const search(Node* a, const int b){
    if(a==nullptr){
        return false;
    }
    if(b<a->key){
        return search(a->left, b);
    }
    else if(b>a->key){
        return search(a->right,b);
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
    return(get_height(a->right)-get_height(a->left));
}
Node* find_min(Node* a){ //searching the minimal element
    if(a==nullptr){
        return a;
    }
    if(a->left==nullptr){
        return a;
    } else
        return find_min(a->left);
}
//Fixing Node
void fix_height(Node& a){
    if(get_height(a.right)>get_height(a.left)){
        a.height=get_height(a.right)+1;
    }else {
        a.height = get_height(a.left) + 1;
    }
}
//Node rotations
Node* rotate_r(Node *a){ //small right rotation
    Node*c=a;
    Node *b=c->left;
    a->left=b->right;
    b->right=c;
    fix_height(*c);
    fix_height(*b);
    return b;
}
Node* rotate_l(Node *a){ //small left rotation
    Node*c=a;
    Node *b=c->right;
    c->right=b->left;
    b->left=c;
    fix_height(*c);
    fix_height(*b);
    return b;
}
Node* big_rotate_r(Node* a){ //big right rotation
    a->left=rotate_l(a->left);
    return rotate_r(a);
}
Node* big_rotate_l(Node* a){ //big left rotation
    a->right=rotate_r(a->right);
    return rotate_l(a);
}
//balancing node
Node* balance(Node* a){
    fix_height(*a);
    if(difference(a)==2){
        if(difference(a->right)<0){
        a=big_rotate_l(a);}else{a=rotate_l(a);}
    }
    if(difference(a)==-2){
        if(difference(a->left)>0){
           a= big_rotate_r(a);}else{a=rotate_r(a);}
    }
    return a;
}
//Node formatting
Node* remove_min(Node* a){ //deleting minimal
    if(a==nullptr){
        throw runtime_error("Can't delete minimal from empty tree!");
    }
    if(a->left==nullptr){
        return a->right;
    }
    a->left=remove_min(a->left);
    return balance(a);
}
Node* insert(Node* a, const int b){ //adding element
    if(a==nullptr){
        return new Node(b);
    }
    if(b<a->key){
        a->left=insert(a->left,b);
    }
    else{
        a->right=insert(a->right,b);
    }
    return a=balance(a);
}
Node* remove(Node* a, const int b){//deleting element
    if(a==nullptr){
        return nullptr;
    }
    if(b<a->key){
        a->left=remove(a->left, b);
    }
    else if(b>a->key){
        a->right=remove(a->right,b);
    }
    else{
        Node* left = a->left;
        Node* right = a->right;
        Node *min= find_min(a);
        delete a;
        if(right==nullptr){
            a=left;
        }
        a=find_min(right);
        if(a!=nullptr) {
            right=remove_min(right);
            a->right=right;
            a->left=left;
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
       del(a->left);
       del(a->right);
       delete a;
       a=nullptr;
   }
}
//operators
ostream& operator<<(ostream &os, const Node& a){
    Node* b=new Node(a);
    Node* i;
    while(b->left!=nullptr){
       i=find_min(b->left);
       cout<< "| "<< i->key <<" | ";
       b->left=remove_min(b->left);
    }
    cout<<"( "<<b->key<<" )";
    while(b->right!=nullptr){
        i=find_min(b->right);
        cout<< " | "<< i->key <<" |";
        b->right=remove_min(b->right);
    }
    delete b,i;
    return os;
}
 **/
#endif