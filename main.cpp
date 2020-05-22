#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "rndm_tree.h"
using namespace std;
typedef int T;


int main() {
RandomTree tree(50);
//tree.TESTING_INSERT(10000000);
//tree.TESTING_MAX_ELEMENT();
//tree.TESTING_DELETING(10000000);
//tree.TESTING_MIN_ELEMENT(10000);
int i=0;
while(i!=1000000) {
    tree.TESTING_MAX_ELEMENT(100000);
    i+=10;
}
int j=0;
    while(j!=1000000) {
        tree.TESTING_MIN_ELEMENT(100000);
        j+=10;
    }
    return 0;
}


