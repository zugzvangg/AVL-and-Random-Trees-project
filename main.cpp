#include <iostream>
#include "AVL.h"
#include "Ran_tree.h"
#include "Tree.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <bits/unique_ptr.h>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    cout<< "Tree test!"<<endl;
    cout<< "creating"<<endl;
AVL<int> a;
RandomTree<int> b(10);
b.TESTING_INSERT(10);
b.TESTING_DELETING(100);
b.MEGA_BANG(100,100,100);
return 0;
}
