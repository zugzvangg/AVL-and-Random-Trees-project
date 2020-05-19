#include <iostream>
#include "Red_Black_Tree.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <bits/unique_ptr.h>
#include <vector>
#include <algorithm>

#ifndef RED_BLACK_TREE_RED_BLACK_TREE_H
#define RED_BLACK_TREE_RED_BLACK_TREE_H

using namespace std;

typedef int T;                  //able to store any type

struct Leaf {
    Leaf* left;
    Leaf* right;
    Leaf* parent;
    typedef enum { black, red } color_of_Leaf;//color of Leaf
    color_of_Leaf color;    //enumed color of leaf
    T data;//data
};

bool InsertionComparator(Leaf* leaf1, Leaf* leaf2)
{
    return leaf1->data<leaf2->data;
}

bool IsInTree(T data, vector<Leaf *> &leaves)
{
    for(auto & leave : leaves)
    {
        if(leave->data==data)
        {
            return true;
        }
    }
    return false;
}

class Red_Black_Tree {
private:
    vector<Leaf *> leaves;
    Leaf *root;
public:
    Red_Black_Tree(T data) {
root->right = nullptr;
root->left= nullptr;
root->data=data;
root->color = Leaf::color_of_Leaf::black;
    }
    Red_Black_Tree(){
        root->right = nullptr;
        root->left= nullptr;
        root->color = Leaf::color_of_Leaf::black;
    }
    int getNumberOfElements()
    {
        return leaves.size();
    }
    T getElement(int i)
    {
        return leaves[i]->data;
    }

    Leaf *insertLeaf(T data) { //inserting leaf with data
        Leaf *current, *parent, *new_leaf = new Leaf;
        current = root;
        parent = nullptr;
        while (current != nullptr) {
            if (data == current->data) //не вставляем, если такой элемент уже есть
            {
                cout << "There is such an element in the tree! You can not put one more!" << endl;
                return (current);
            }
            else
            {
                parent = current;
                if(data<current->data)
                {
                    current=current->left;
                }
                else {
                    current = current->right;
                }
            }
        }
        new_leaf->data = data;
        new_leaf->parent = parent;
        new_leaf->left = nullptr;
        new_leaf->right = nullptr;
        new_leaf->color = Leaf::color_of_Leaf::red;
        if(parent) {
            if(data < parent->data)
            { parent->left = new_leaf;
            cout << "Successful insertion of the left child! Congrats! It's value="<< data <<endl;}
            else if(data>parent->data){
                parent->right = new_leaf;
                cout << "Successful insertion of the right child Congrats! It's value="<<data<<endl;
                }
            else
            {
                cout << "There is such an element in the tree! You can not put one more!" << endl;
                return nullptr;
            }
        //insertFixup(new_leaf);
        leaves.push_back(new_leaf);
        sort(leaves.begin(), leaves.end(), InsertionComparator);
        return(new_leaf);
    }

    }

    Leaf*findNode(T data) { //looking for a leaf with this data in

        Leaf *current = root;
        while(current != nullptr)
            if(data == current->data)
            {
                cout << "There is such an element in the tree! It's value=" << data<<endl;
                return (current);
            }
            else if (data<current->data)
            {
                current=current->left;
            }
            else
                {
                current=current->right;
                }
            cout << "There is no an element with data="<< data << endl << "):" << endl;
            return nullptr;
    }
    void deleteNode(T data) { //удаляет узел с указанным data
        Leaf *current = root;
        if (!IsInTree(data, leaves)) {
            cout << "There is no such element. It's impossible to delete! It's value=" << data << endl;
            delete current;
            return;
        } else {
            while (current!= nullptr)
                if (data == current->data) {
                    if(current->left== nullptr && current->right== nullptr)
                    {
                        current->parent->left= nullptr;
                        current->parent->right= nullptr;
                        delete current;
                        cout << "Element " << data << " is deleted! It was the leaf of the tree.";
                    }//обработка всех случае удаления элемента
                } else if (data < current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }

        }
    }

};


int main() {
    Red_Black_Tree tree;
    tree.insertLeaf(1);
    tree.insertLeaf(1);
    tree.insertLeaf(2);
    tree.insertLeaf(3);
    tree.findNode(1);
    tree.findNode(4);
    tree.deleteNode(7);
    tree.deleteNode(3);
    for(int i=0; i<tree.getNumberOfElements(); i++)
    {
        cout << tree.getElement(i) << " ";
    }
    cout << endl;
    cout << tree.getElement(2);
    return 0;
}

#endif //RED_BLACK_TREE_RED_BLACK_TREE_H
