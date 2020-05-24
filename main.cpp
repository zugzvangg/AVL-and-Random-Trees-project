#include <iostream>
#include "AVL.h"
#include "rndm_tree.h"
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
RandomTree <int>b(10);
b.INSERT(b.getRoot(), 6);
b.INSERT(b.getRoot(), 8);
b.INSERT(b.getRoot(), 1);
b.INSERT(b.getRoot(), 10);
b.INSERT(b.getRoot(), 12);
b.INSERT(b.getRoot(), 50);
b.DELETE(b.getRoot(), 8);
b.DELETE(b.getRoot(), 6);
//b.MEGA_BANG(1000, 20, 1100);
a.MEGA_BANG(1000, 20, 1000);

return 0;
}
