
#ifndef TREE_H
#define TREE_H
#include "Timer.h"
#include <fstream>
#include "AVL_Node.h"
#include "rndm_tree.h"
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <iomanip>
using namespace std;
template <typename T>
class Tree {
public:
//interface methods;
    virtual T FIND_MIN_ELEMENT(){};                          //minimal element
    virtual T FIND_MAX_ELEMENT(){};                          //maximal element
    virtual Node<T>* FIND_NODE(T data){};                    //search with key
    virtual void INSERT(T data){};                           //insertion
    virtual void DELETE(T data){};                           //deleting
//interface tests //enter amount of elements for every test
    virtual double TESTING_INSERT(int n) final;
    virtual double TESTING_DELETING(int n) final;
    virtual double TESTING_MAX_ELEMENT(int n) final;
    virtual double TESTING_MIN_ELEMENT(int n) final;
    virtual double TESTING_FINDING_ELEMENT(int n) final;
//interface output of testing data
    virtual void MEGA_BANG(int start,int step, int cycles) final; //the biggest *ucking test ever with output!
    //first input starting number of elements, then amount of adding elements pers step, then amount of these steps.
};
//test funcs declaration
template <typename T>double Tree<T>::TESTING_INSERT(int n)
{
    Timer t;
    for(int i=0; i<n; i++) {
        INSERT(i);
    }
    cout << "Time of inserting of " << n << " elements is " <<  t.elapsed() << " s "<< endl;
    Timer a;
    INSERT(n);
    cout << "Time of inserting of 1 element into the tree of " << n << " elements is " << a.elapsed() << " ms " << endl<<endl;
    return a.elapsed();
}         //insertion test

template <typename T>double Tree<T>::TESTING_DELETING(int n)
{
    for(int i=0; i<n; i++) {
        INSERT(i);
    }
    Timer a;
    INSERT(n);
    DELETE(n-1);
    cout << "Time of deleting of an element is " << a.elapsed()  << "ms" << endl<<endl;
    return a.elapsed();
}        //deleting test

template <typename T>double Tree<T>::TESTING_MAX_ELEMENT(int n)
{
    unsigned int start_time =  clock();
    for(int i=0; i<n; i++) {
        INSERT(i);
    }
    Timer a;
    FIND_MAX_ELEMENT();
    cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    return a.elapsed();
}     //max test

template <typename T>double Tree<T>::TESTING_MIN_ELEMENT(int n)
{
    unsigned int start_time =  clock();
    for(int i=0; i<n; i++) {
        INSERT(i);
    }
    Timer a;
    FIND_MIN_ELEMENT();
    cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    return a.elapsed();
}     //min test

template <typename T>double Tree<T>::TESTING_FINDING_ELEMENT(int n)
{
    unsigned int start_time =  clock();
    for(int i=0; i<n; i++) {
        INSERT(i);
    }
    Timer a;
    FIND_NODE(n-1);
    cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    return a.elapsed();
} //search test

template <typename T>void Tree<T>::MEGA_BANG(int start,int step, int cycles){
    ofstream fout("info.dat");
    cout<< "insert delete min max search"<<endl;
    fout<< "insert delete min max search"<<endl;
    for(int i=start;i<(start+step*cycles);i+=step) {
        fout << endl << setprecision(10) << this->TESTING_INSERT(i) << " "           //insert output
             << this->TESTING_DELETING(i) << " "                                        //delete output
             << this->TESTING_MAX_ELEMENT(i) << " "                                     //max output
             << this->TESTING_MIN_ELEMENT(i) << " "                                     //min output
             << this->TESTING_FINDING_ELEMENT(i);                                       //searching output
    };
    fout.close();
} //total checkout! outputting into "info.dat"
#endif //TREE_H
