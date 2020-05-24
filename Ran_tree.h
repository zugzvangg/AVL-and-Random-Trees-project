
#ifndef RAN_TREE_H
#define RAN_TREE_H
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <chrono>
#include "Timer.h"
#include "AVL_Node.h"
#include "Tree.h"
#include <iomanip>
#include <fstream>
template <typename T> class RandomTree: public Tree<T>{
private:
    Node<T> *root;
    int number_of_elements;

    int getNumberOfElements()
    {
        return root->s;
    }

    static Node<T>* findRecursion(Node<T>* rec, T key) // рекурсивный поиск
    {
        if( rec == nullptr )
        {
            cout << "No of this element in the tree"<<endl;
            return nullptr;
        }
        if( key == rec->key ){
            cout << "Your element is found!"<<endl;
            return rec;}
        if( key < rec->key )
            return findRecursion(rec->l,key);
        else
            return findRecursion(rec->r,key);
    }


    static int getsize(Node<T>* nd) //получить размер
    {
        if( nd== nullptr)
        {return 0;}
        else return nd->s;
    }

    static void SetSize(Node<T>* p) // рекурсивно задать размер дерева
    {
        p->s = getsize(p->l)+getsize(p->r)+1;
    }

    static Node<T>* RightRotation(Node<T>* x) //правое вращение
    {
        Node<T>* y = x->l;
        x->l = y->r;
        y->r = x;
        y->s = x->s;
        SetSize(x);
        return y;
    }

    static Node<T>* LeftRotation(Node<T>* x) //левое вращение
    {
        Node<T>* y = x->r;
        x->r = y->l;
        y->l = x;
        y->s = x->s;
        SetSize(x);
        return y;
    }
    static Node<T>* InsertRoot(Node<T>* p, T key) //вставка корня(одна из вспомогательных функций)
    {
        if( p== nullptr )
        {
            Node<T>* nd = new Node<T>(0);
            nd->s=1;
            nd->key=key;
            nd->r= nullptr;
            nd->l= nullptr;
            return nd;
        }else
        {
            if( key<p->key )
            {
                p->l = InsertRoot(p->l,key);
                return RightRotation(p);
            }
            else
            {
                p->r = InsertRoot(p->r,key);
                return LeftRotation(p);
            }
        }
    }

    static Node<T>* join(Node<T>* p, Node<T>* q) // слияние деревьев
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

    RandomTree(T key) {
        root = new Node<T>(0);
        root->r = nullptr;
        root->l = nullptr;
        root->key = key;
        root->s=1;
        number_of_elements = 1;

    }

    Node<T>* getRoot() //указатель на корень
    {
        return root;
    }

    T FIND_MIN_ELEMENT() //минимальный элемент
    {
        Node<T> *current = root->r;
        while(current->l!= nullptr)
        {
            current=current->l;
        }
        cout << "Minimal element in the tree = " << current->key << endl<<endl;
        return current->key;
    }
    T FIND_MAX_ELEMENT() //максимальный элемент
    {
        Node<T> *current = root;
        while(current->r!=nullptr)
        {
            current=current->r;
        }
        cout << "Maximal element in the tree = " << current->key << endl;
        return current->key;
    }

    Node<T> *FIND_NODE(T key) { //поиск по ключу
        Node<T> *current = root;
        while (current != nullptr)
            if (key == current->key) {
                cout << "There is an element = " << key << " in the tree"<<endl;
                return (current);
            } else if (key < current->key) {
                current = current->l;
            } else {
                current = current->r;
            }
        cout << "There is no such element"<<endl;
        return nullptr;
    }

    static Node<T>* INSERT(Node<T>* p, T key) //вставка большими буквами необходимые функции - остальные вспомогательные
    {
        if( p== nullptr )
        {
            p = new Node<T>(0);
            p->s=1;
            p->key=key;
            p->r= nullptr;
            p->l= nullptr;
            return p;
        }
        if( rand()%(p->s+1)==0 )
            return InsertRoot(p,key);
        if( p->key>key )
            p->l = INSERT(p->l,key);
        else
            p->r = INSERT(p->r,key);
        SetSize(p);
        return p;

    }
    void DELETE(T key) // удаление элемента
    {
        this->root = AVL_TREE_NODE_H::remove(root,key);

    }

    double TESTING_INSERT(int n)
    {
        double time;
        Timer t;
        for(int i=0; i<n; i++) {
            this->root= INSERT(root,i);
        }
        time=t.elapsed();
        cout << "Time of inserting of " << n << " elements is " <<  t.elapsed() << " s "<< endl;
        Timer a;
        INSERT(getRoot(),n);
        cout << "Time of inserting of 1 element into the tree of " << n << " elements is " << a.elapsed() << " ms " << endl<<endl;
        for(int i=0; i<n+1; i++) {
            DELETE(i);
        }
        return time;
    }

    double TESTING_DELETING(int n)
    {
        double time;
        for(int i=0; i<n; i++) {
            this->root= INSERT(root,i);
        }
        Timer a;
        for(int i=0; i<n; i++) {
            DELETE(i);
        }
        time=a.elapsed();
        cout << "Time of deleting of an element is " << a.elapsed()  << "ms" << endl<<endl;
        return time;
    }

    double TESTING_MAX_ELEMENT  (int n) override
    {
        double time;
        unsigned int start_time =  clock();
        for(int i=0; i<n; i++) {
           this->root= INSERT(root,i);
        }
        Timer a;
        FIND_MAX_ELEMENT();
        time=a.elapsed();
        cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
        for(int i=0; i<n; i++) {
            DELETE(i);
        }
        return time;
    }

    double TESTING_MIN_ELEMENT(int n)
    {
        double time;
        unsigned int start_time =  clock();
        for(int i=0; i<n; i++) {
            this->root= INSERT(root,i);
        }
        Timer a;
        FIND_MIN_ELEMENT();
        time=a.elapsed();
        cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
        for(int i=0; i<n; i++) {
            DELETE(i);
        }
        return time;
    }

    double TESTING_FINDING_ELEMENT(int n)
    {
        double time;
        unsigned int start_time =  clock();
        for(int i=0; i<n; i++) {
            this->root= INSERT(root,i);
        }
        Timer a;
        FIND_NODE(n-1);
        time=a.elapsed();
        cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
        for(int i=0; i<n; i++) {
            DELETE(i);
        }
        return time;
    }

    void MEGA_BANG(int start,int step, int cycles){
        ofstream fout("info.dat");
        cout<< "insert delete min max search"<<endl;
        fout<< "keys insert delete min max search"<<endl;
        for(int i=start;i<(start+step*cycles);i+=step) {
            fout << endl << setprecision(10) <<  i << " " <<this->TESTING_INSERT(i) << " "           //insert output
                 << this->TESTING_DELETING(i) << " "                                        //delete output
                 << this->TESTING_MAX_ELEMENT(i) << " "                                     //max output
                 << this->TESTING_MIN_ELEMENT(i) << " "                                     //min output
                 << this->TESTING_FINDING_ELEMENT(i);                                       //searching output
        };
        fout.close();
    } //total checkout! outputting into "info.dat"

};

#endif //RAN_TREE_H
