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
    RandomTree<int> b(0);
AVL<int> a;
a.insert({228,322,1337,1,2,3,4,5,6,7,8,9,10});
a.Print_beauty();
b.INSERT(b.getRoot(),2);
b.INSERT(b.getRoot(),3);
b.INSERT(b.getRoot(),4);
b.Print_beauty();
return 0;
}
