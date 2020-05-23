#include <iostream>
#include "AVL.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <bits/unique_ptr.h>
#include <vector>
#include <algorithm>
using namespace std;
int main(void) {
    cout<< "AVL test!"<<endl;
    cout<< "creating"<<endl;
AVL<int> a;
AVL<bool> b(1);
a.insert(228);
a.insert({1,2,3,322,228,322});
cout<< a.amount()<<endl;
cout<< a.search(228)<<endl;
AVL<int> c(a);
a.remove_element(228);
cout<< a.amount()<<endl;
a.remove_element({1,2,3});
cout<< a.amount()<<endl;
cout<< a.search(228)<<endl;
cout<< a.search(1)<<endl;
cout<< a;
cout<< b;
//interface check
a.INSERT(15);
a.FIND_MIN_ELEMENT();
a.FIND_MAX_ELEMENT();
a.FIND_NODE(322);
a.DELETE(322);
a.TESTING_INSERT(2);
a.TESTING_DELETING(2);
a.TESTING_FINDING_ELEMENT(1);
a.TESTING_MAX_ELEMENT(1);
a.TESTING_MIN_ELEMENT(1);
a.MEGA_BANG(1,10,3);
return 0;
}
