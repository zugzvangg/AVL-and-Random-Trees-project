
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <chrono>
#include "Timer.h"

using namespace std;
typedef int T;

#ifndef RED_BLACK_TREE_RANDOM_TREE_H
#define RED_BLACK_TREE_RANDOM_TREE_H


struct Node // структура для представления узлов дерева
{
    T data;
    int s;
    Node* l;
    Node* r;
};

class RandomTree {
private:
    vector<Node *> leaves;
    Node *root;
    int number_of_elements;


    int getNumberOfElements()
    {
        return root->s;
    }


    Node* getRoot() //указатель на корень
    {
        return root;
    }

    static Node* findRecursion(Node* rec, int data) // рекурсивный поиск
    {
        if( rec == nullptr )
        {
            cout << "No of this element in the tree"<<endl;
            return nullptr;
        }
        if( data == rec->data ){
            cout << "Your element is found!"<<endl;
            return rec;}
        if( data < rec->data )
            return findRecursion(rec->l,data);
        else
            return findRecursion(rec->r,data);
    }


    static int getsize(Node* nd) //получить размер
    {
        if( nd== nullptr)
        {return 0;}
        else return nd->s;
    }

    static void SetSize(Node* p) // рекурсивно задать размер дерева
    {
        p->s = getsize(p->l)+getsize(p->r)+1;
    }

    static Node* RightRotation(Node* x) //правое вращение
    {
        Node* y = x->l;
        x->l = y->r;
        y->r = x;
        y->s = x->s;
        SetSize(x);
        return y;
    }

    static Node* LeftRotation(Node* x) //левое вращение
    {
        Node* y = x->r;
        x->r = y->l;
        y->l = x;
        y->s = x->s;
        SetSize(x);
        return y;
    }
    static Node* InsertRoot(Node* p, T data) //вставка корня(одна из вспомогательных функций)
    {
        if( p== nullptr )
        {
            Node* nd = new Node;
            nd->s=1;
            nd->data=data;
            nd->r= nullptr;
            nd->l= nullptr;
            return nd;
        }else
        {
            if( data<p->data )
            {
                p->l = InsertRoot(p->l,data);
                return RightRotation(p);
            }
            else
            {
                p->r = InsertRoot(p->r,data);
                return LeftRotation(p);
            }
        }
    }

    static Node* join(Node* p, Node* q) // слияние деревьев
    {
        if( p== nullptr ) return q;
        if( q== nullptr ) return p;
        if(p->s > rand() % (p->s + q->s))
        {
            p->r = join(p->r,q);
            SetSize(p);
            return p;
        }
        else
        {
            q->l = join(p,q->l);
            SetSize(q);
            return q;
        }
    }


public:
    ~RandomTree() {
        delete root;
    }

    RandomTree(T data) {
        root = new Node;
        root->r = nullptr;
        root->l = nullptr;
        root->data = data;
        root->s=1;
        number_of_elements = 1;

    }

    T FIND_MIN_ELEMENT() //минимальный элемент
    {
        Node *current = root->r;
        while(current->l!= nullptr)
        {
            current=current->l;
        }
        cout << "Minimal element in the tree = " << current->data << endl<<endl;
        return current->data;
    }
    T FIND_MAX_ELEMENT() //максимальный элемент
    {
        Node *current = root;
        while(current->r!=nullptr)
        {
            current=current->r;
        }
        cout << "Maximal element in the tree = " << current->data << endl;
        return current->data;
    }

    Node *FIND_NODE(T data) { //поиск по ключу
        Node *current = root;
        while (current != nullptr)
            if (data == current->data) {
                cout << "There is an element = " << data << " in the tree"<<endl;
                return (current);
            } else if (data < current->data) {
                current = current->l;
            } else {
                current = current->r;
            }
        cout << "There is no such element"<<endl;
        return nullptr;
    }


    static Node* INSERT(Node* p, T data) //вставка большими буквами необходимые функции - остальные вспомогательные
    {
        if( p== nullptr )
        {
            Node* nd = new Node;
            nd->s=1;
            nd->data=data;
            nd->r= nullptr;
            nd->l= nullptr;
            return nd;
        }
        if( rand()%(p->s+1)==0 )
            return InsertRoot(p,data);
        if( p->data>data )
            p->l = INSERT(p->l,data);
        else
            p->r = INSERT(p->r,data);
        SetSize(p);
        return p;
    }

    static Node* DELETE(Node* nd, int data) // удаление элемента
    {
        if( nd== nullptr )
        {
            cout << "It's nullptr, it's impossible to delete"<<endl;
            return nd;
        }
        if( nd->data==data )
        {
            Node* nd2 = join(nd->l,nd->r);
            delete nd;
            cout << "Element = "<< data << " is deleted" << endl<<endl;
            return nd2;
        }
        else if( data<nd->data )
            nd->l = DELETE(nd->l,data);
        else
            nd->r = DELETE(nd->r,data);
        return nd;

    }

    void TESTING_INSERT(int n)
    {
        Timer t;
        for(int i=0; i<n; i++) {
            INSERT(getRoot(), i);
        }
        cout << "Time of inserting of " << n << " elements is " <<  t.elapsed() << " s "<< endl;
        Timer a;
        INSERT(getRoot(), n);
        cout << "Time of inserting of 1 element into the tree of " << n << " elements is " << a.elapsed() << " ms " << endl<<endl;
    }

    void TESTING_DELETING(int n)
    {
        for(int i=0; i<n; i++) {
            INSERT(getRoot(), i);
        }
        Timer a;
        INSERT(getRoot(), n);
        DELETE(getRoot(), n-1);
        cout << "Time of deleting of an element is " << a.elapsed()  << "ms" << endl<<endl;
    }

    void TESTING_MAX_ELEMENT(int n)
    {
        unsigned int start_time =  clock();
        for(int i=0; i<n; i++) {
            INSERT(getRoot(), i);
        }
        Timer a;
        FIND_MAX_ELEMENT();
        cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    }

    void TESTING_MIN_ELEMENT(int n)
    {
        unsigned int start_time =  clock();
        for(int i=0; i<n; i++) {
            INSERT(getRoot(), i);
        }
        Timer a;
        FIND_MIN_ELEMENT();
        cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    }

    void TESTING_FINDING_ELEMENT(int n)
    {
        unsigned int start_time =  clock();
        for(int i=0; i<n; i++) {
            INSERT(getRoot(), i);
        }
        Timer a;
        FIND_NODE(n-1);
        cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    }

};


#endif //RED_BLACK_TREE_RANDOM_TREE_H

