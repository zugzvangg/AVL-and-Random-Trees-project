#include <iostream>
#include "AVL.h"
#include "AVL_Node.h"
using namespace std;
int main() {
    Node* k=new Node(2);
AVL a,b,c;
a.insert(2);
    a.insert(228);
    a.insert(322);
    a.insert(33);
a.insert({1,2,3,4});
cout << a<<endl;
a.remove_element(3);
cout<< a<<endl;
    c=a;
cout<<c<<endl;

return 0;
}
