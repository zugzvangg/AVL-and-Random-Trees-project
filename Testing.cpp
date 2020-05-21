//How we were testing

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "random_tree.h">
#include "Tests.h"
using namespace std;
typedef int T;


int main() {
RandomTree tree(50);
        unsigned int start_time =  clock(); // начальное время
        for(int i=5; i<1000000; i++) {
            tree.Insert(tree.getRoot(), i);
        }
        unsigned int end_time = clock(); // конечное время
        unsigned int search_time = end_time - start_time;
        cout << "Inseterting time " << search_time<< endl;
    unsigned int start_time1 =  clock(); // начальное время
    tree.findMaxElement();
    unsigned int end_time1 = clock(); // конечное время
    unsigned int search_time1 = end_time - start_time;
cout << search_time1<<endl;
    unsigned int start_time2 =  clock(); // начальное время
    tree.Deleting(tree.getRoot(), 100);
    unsigned int end_time2 = clock(); // конечное время
    unsigned int search_time2 = end_time - start_time;
cout << search_time2<<endl;
    unsigned int start_time3 =  clock(); // начальное время
    tree.findNodeByData(-150);
    unsigned int end_time3 = clock(); // конечное время
    unsigned int search_time3 = end_time - start_time;
    cout << search_time3<<endl;
    return 0;
}


