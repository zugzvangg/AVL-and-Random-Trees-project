
#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H
#include <iostream>
using namespace std;
//Node building
struct Node {
    int key;
    Node *left, *right;
    unsigned int height;
    Node(int key) { this->key = key; left = nullptr; right = nullptr; height = 1; };
    Node(const Node &a){this->key=a.key;this->left=a.left;this->right=a.right;this->height=a.height;};
};
//Finding out Node info
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
            remove_min(right);
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
Node* delete_n(Node* a){
    if(a!=nullptr){
        if(a!=nullptr)
        a->right=delete_n(a->right);
        if(a!=nullptr)
        a->left=delete_n(a->left);
        delete a;
        a=nullptr;
    }
    return nullptr;
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
#endif