#include <iostream>
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
typedef int T;
struct Leaf {
    Leaf* l;
    Leaf* r;
    Leaf* par;
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
    int number_of_elements;
public:
    Red_Black_Tree(T data) {
        root = new Leaf;
        root->r = nullptr;
        root->l = nullptr;
        root->data = data;
        root->color = Leaf::color_of_Leaf::black;
        number_of_elements=1;

    }

    Red_Black_Tree() {
        root = new Leaf;
        root->r = nullptr;
        root->l = nullptr;
        root->data=0;
        root->color = Leaf::color_of_Leaf::black;
        number_of_elements=1;
    }
    ~Red_Black_Tree()
    {
        delete root;
    }

    int NumberOfElements()
    {
        return number_of_elements;
    }

    T getElement(int i) {
        return leaves[i]->data;
    }

    Leaf *insertLeaf(T data) { //inserting leaf with data
        Leaf *current, *par, *new_leaf = new Leaf;
        number_of_elements++;
        current = root;
        par = nullptr;
        while (current != nullptr) {
            if (data == current->data) //не вставляем, если такой элемент уже есть
            {
                cout << "There is such an element in the tree! You can not put one more!" << endl;
                return (current);
            } else {
                par = current;
                if (data < current->data) {
                    current = current->l;
                } else {
                    current = current->r;
                }
            }
        }
        new_leaf->data = data;
        new_leaf->par = par;
        new_leaf->l = nullptr;
        new_leaf->r = nullptr;
        new_leaf->color = Leaf::color_of_Leaf::black;
        if (par) {
            if (data < par->data) {
                par->l = new_leaf;
                cout << "Successful insertion of the left child! Congrats! It's value=" << par->l->data << endl;
                cout << "Do u want to balance th tree? 1=Yes. 0=No"<<endl;
                int ans;
                cin >> ans;
                if(ans==1)
                {
                    FixingAfterInsertion(par->l); //удобное подключение балансировки после вставки
                    cout << "Your tree is balanced"<<endl;
                }
                else if(ans==0)
                {
                    cout << "As u want:)"<<endl;
                }
                else cout << "No way! Wrong answer! No balance!";
            } else if (data > par->data) {
                par->r = new_leaf;
                cout << "Successful insertion of the left child! Congrats! It's value=" << par->r->data << endl;
                cout << "Do u want to balance th tree? 1=Yes. 0=No"<<endl;
                int ans;
                cin >> ans;
                if(ans==1)
                {
                    FixingAfterInsertion(par->r); //удобное подключение балансировки после вставки
                    cout << "Your tree is balanced"<<endl;
                }
                else if(ans==0)
                {
                    cout << "As u want:)"<<endl;
                }
                else cout << "No way! Wrong answer! No balance!";
            }
            leaves.push_back(new_leaf);
            sort(leaves.begin(), leaves.end(), InsertionComparator);
            return (new_leaf);
        }
    }

    static bool IsRed(Leaf* x)
    {
            return x->color == Leaf::color_of_Leaf::red;
    }

    bool IsBlack(Leaf* x)
    {
            return x->color == Leaf::color_of_Leaf::black;
    }

     void FixingAfterInsertion(Leaf *x) {
         while (x != root && IsRed(x->par)) {
             if (x->par == x->par->par->l) {
                 Leaf *y = x->par->par->r;
                 if (IsRed(y)) {
                     x->par->color = Leaf::color_of_Leaf::black;;
                     y->color = Leaf::color_of_Leaf::black;;
                     x->par->par->color = Leaf::color_of_Leaf::red;
                     x = x->par->par;
                 } else {
                     if (x == x->par->r) {
                         x = x->par;
                         LeftRotation(x);
                     }
                     x->par->color = Leaf::color_of_Leaf::black;;
                     x->par->par->color = Leaf::color_of_Leaf::red;
                     rightRotation(x->par->par);
                 }
             } else {
                 Leaf *y = x->par->par->l;
                 if (y->color == Leaf::color_of_Leaf::red) {
                     x->par->color = Leaf::color_of_Leaf::black;
                     y->color = Leaf::color_of_Leaf::black;
                     x->par->par->color = Leaf::color_of_Leaf::red;
                     x = x->par->par;
                 } else {

                     if (x == x->par->l) {
                         x = x->par;
                         rightRotation(x);
                     }
                     x->par->color = Leaf::color_of_Leaf::black;
                     x->par->par->color = Leaf::color_of_Leaf::red;
                     LeftRotation(x->par->par);
                 }
             }
         }
         root->color = Leaf::color_of_Leaf::black;
    }
    
    void LeftRotation(Leaf *x) {
        Leaf *y = x->r;
        x->r = y->l;
        if (y->l != nullptr) y->l->par = x;
        y->par = x->par;
        if (x->par) {
            if (x == x->par->l)
                x->par->l = y;
            else
                x->par->r = y;
        } else {
            root = y;
        }
        y->l = x;
        x->par = y;
        cout << "Your tree is rotated to the left!"<<endl;
   }

    void rightRotation(Leaf *x) {
        Leaf *y = x->l;
        x->l = y->r;
        if (y->r != nullptr) y->r->par = x;
        y->par = x->par;
        if (x->par) {
            if (x == x->par->r)
                x->par->r = y;
            else
                x->par->l = y;
        } else {
            root = y;
        }
        y->r = x;
        x->par = y;
        cout << "Your tree is rotated to the right!" <<endl;
   }

    Leaf *findNode(T data) {
        Leaf *current = root;
        while (current != nullptr)
            if (data == current->data) {
                return (current);
            } else if (data < current->data) {
                current = current->l;
            } else {
                current = current->r;
            }
    }

    Leaf *findNodeByData(T data) { //looking for a leaf with this data in

        Leaf *current = root;
        while (current != nullptr)
            if (data == current->data) {
                cout << "There is such an element in the tree! It's value=" << current->data << "You found it!" << endl;
                return (current);
            } else if (data < current->data) {
                current = current->l;
            } else {
                current = current->r;
            }
        cout << "We can not find it! There is no an element with data=" << data << endl << "):" << endl;
        return nullptr;
    }

    void deleteNode(T data) {
        if (!IsInTree(data, leaves)) {
            cout << "There is no element = " << data << " in this tree. It is impossible to delete" << endl;
            return;
        }
        number_of_elements--;
        Leaf *x, *y;
        Leaf *z = findNode(data);
        cout << "We are going to delete the element = " << z->data << endl;
        if (z->l == nullptr && z->r == nullptr) {
            leaves.erase(find(leaves.begin(), leaves.end(), z));
            z->par->l = nullptr;
            z->par->r= nullptr;
            cout << "The element is deleted. It was on the bottom of the tree" << endl;
        } else if (z->l == nullptr && z->r != nullptr) {
            leaves.erase(find(leaves.begin(), leaves.end(), z));
            z->par->r = z->r;
            z->l = nullptr;
            cout << "We deleted element with value = " << data << ". It had the only right child" << endl;
        } else if (z->l != nullptr && z->r == nullptr) {
            leaves.erase(find(leaves.begin(), leaves.end(), z));
            z->par->l = z->l;
            z->l->r = nullptr;
            cout << "We deleted element with value = " << data << ". It had the only left child" << endl;
        } else if (z->l != nullptr && z->r != nullptr) {
            leaves.erase(find(leaves.begin(), leaves.end(), z));
            return;
//дописать что если оба ребенка есть

        }
        cout << "We need to fix your tree after deleting of the element!"<<endl;
        //deleteFixup(z);
        cout << "It is fixed!" << endl;
        return;
    }

};

int main() {
    Red_Black_Tree tree;
    tree.insertLeaf(-1);
    tree.insertLeaf(1);
    tree.insertLeaf(5);
    tree.insertLeaf(2);
    tree.insertLeaf(3);
    tree.insertLeaf(-5);
    tree.insertLeaf(-2);
    tree.deleteNode(-5);
    tree.deleteNode(-2);
    tree.deleteNode(3);
    tree.deleteNode(5);
    for(int i=0; i<tree.NumberOfElements(); i++)
    {
        cout << tree.findNode(i)->data << " ";
    }
    cout << endl;
    return 0;
}

#endif //RED_BLACK_TREE_RED_BLACK_TREE_H
