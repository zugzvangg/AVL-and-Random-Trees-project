
#ifndef UNTITLED1_SETTEST_H
#define UNTITLED1_SETTEST_H
#include "Beautiful_print.h"
#include "Timer.h"
#include <fstream>
#include "AVL_Node.h"
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <set>
//the same deal for set
template <typename T>double TESTING_INSERT(set<T> bae,int n)
{
    double time;
    Timer t;
    for(int i=0; i<n; i++) {
        bae.insert(i);
    }
    time=t.elapsed();
    cout << "Time of inserting of " << n << " elements is " <<  t.elapsed() << " s "<< endl;
    Timer a;
    bae.insert(n);
    cout << "Time of inserting of 1 element into the tree of " << n << " elements is " << a.elapsed() << " ms " << endl<<endl;
    for(int i=0; i<n+1; i++) {
        bae.erase(i);
    }
    return time;
}         //insertion test

template <typename T>double TESTING_DELETING(set<T> bae,int n)
{
    double time;
    for(int i=0; i<n; i++) {
        bae.insert(i);
    }
    Timer a;
    for(int i=0; i<n; i++) {
        bae.erase(i);
    }
    time=a.elapsed();
    cout << "Time of deleting of an element is " << a.elapsed()  << "ms" << endl<<endl;
    return time;
}        //deleting test

template <typename T>double TESTING_MAX_ELEMENT(set<T> bae,int n)
{
    double time;
    unsigned int start_time =  clock();
    for(int i=0; i<n; i++) {
        bae.insert(i);
    }
    Timer a;
    T max;
    max=*bae.rbegin();
    time=a.elapsed();
    cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    for(int i=0; i<n; i++) {
        bae.erase(i);
    }
    return time;
}     //max test

template <typename T>double TESTING_MIN_ELEMENT(set<T> bae,int n)
{
    double time;
    unsigned int start_time =  clock();
    for(int i=0; i<n; i++) {
        bae.insert(i);
    }
    Timer a;
    T max;
    max=*bae.begin();
    time=a.elapsed();
    cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    for(int i=0; i<n; i++) {
        bae.erase(i);
    }
    return time;
}     //min test

template <typename T>double TESTING_FINDING_ELEMENT(set<T> bae,int n)
{
    double time;
    unsigned int start_time =  clock();
    for(int i=0; i<n; i++) {
        bae.insert(i);
    }
    Timer a;
    bae.find(n-1);
    time=a.elapsed();
    cout << "Time of finding of a needed element in a tree of " << n << " elements is " <<  a.elapsed() << "s"<< endl;
    for(int i=0; i<n; i++) {
        bae.erase(i);
    }
    return time;
} //search test

template <typename T>void MEGA_BANG(int start,int step, int cycles, set<T> bae){
    ofstream fout("info.dat");
    cout<< "insert delete min max search"<<endl;
    fout<< "keys insert delete min max search"<<endl;
    for(int i=start;i<(start+step*cycles);i+=step) {
        fout << endl << setprecision(10) <<  i << " " <<TESTING_INSERT(bae,i) << " "           //insert output
             << TESTING_DELETING(bae,i) << " "                                        //delete output
             << TESTING_MAX_ELEMENT(bae,i) << " "                                     //max output
             << TESTING_MIN_ELEMENT(bae,i) << " "                                     //min output
             << TESTING_FINDING_ELEMENT(bae,i);                                       //searching output
    };
    fout.close();
} //total checkout! outputting into "info.dat"
#endif //UNTITLED1_SETTEST_H
