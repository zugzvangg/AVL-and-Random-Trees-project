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
#include "SETTEST.h"
#include <set>
using namespace std;
int main() {
    cout<< "Tree test!"<<endl;
    RandomTree<int> b(0);
AVL<int> a;
for(int i=0;i<20;++i){
    b.INSERT(b.getRoot(),i);
    a.INSERT(228*i);
}
b.Print_beauty();
cout<<endl;
a.Print_beauty();
set<int> q;
MEGA_BANG(1,3,3,q);
return 0;
}
