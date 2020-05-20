#include <iostream>
#include "AVL.h"
#include "Red_Black_Tree.h"
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
AVL a;
    cout<< "output"<<endl;
    cout<< a << endl;
    cout<< "inserting 228"<<endl;
    a.insert(228);
    cout<< a << endl;
    cout<< a.amount()<<endl;
    cout<< "inserting mass {1337,322,1,2,3}"<<endl;
    a.insert ({1337,322,1,2,3});
    cout<< a << endl;
    cout<< a.amount()<<endl;
    cout<< "removing 322"<<endl;
    a.remove_element(322);
    cout<< a << endl;
    cout<< a.amount()<<endl;
    cout<< "removing mass {1,2,322}"<<endl;
    a.remove_element({1,2,322});
    cout<< a << endl;
    cout<< a.amount()<<endl;
return 0;
}
