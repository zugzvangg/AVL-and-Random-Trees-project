#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;
typedef int T;

struct Node // структура для представления узлов дерева
{
    T data;
    int s;
    Node* l;
    Node* r;
};

class RandomTree {
private:
    vector<Node *> leaves;
    Node *root;
    int number_of_elements;
public:
    RandomTree(T data) {
        root = new Node;
        root->r = nullptr;
        root->l = nullptr;
        root->data = data;
        root->s=1;
        number_of_elements = 1;

    }

    ~RandomTree() {
        delete root;
    }

    int getNumberOfElements()
    {
        return root->s;
    }

    T findMinimalElement()
    {
        Node *current = root;
        while(current->l!= nullptr)
        {
            current=current->l;
        }
        cout << "Minimal element in the tree = " << current->data << endl<<endl;
        return current->data;
    }
    T findMaxElement()
    {
        Node *current = root;
        while(current->r!=nullptr)
        {
            current=current->r;
        }
        cout << "Maximal element in the tree = " << current->data << endl<<endl;
        return current->data;
    }

    Node* getRoot()
    {
        return root;
    }

    static Node* findRecursion(Node* rec, int data) // поиск ключа k в дереве p
    {
        if( rec == nullptr )
        {
            cout << "No of this element in the tree"<<endl;
            return nullptr;
        }
        if( data == rec->data ){
            cout << "Your element is found!"<<endl;
            return rec;}
        if( data < rec->data )
            return findRecursion(rec->l,data);
        else
            return findRecursion(rec->r,data);
    }

    Node *findNodeByData(T data) { //looking for a leaf with this data in
        Node *current = root;
        while (current != nullptr)
            if (data == current->data) {
                cout << "There is an element = " << data << " in the tree"<<endl;
                return (current);
            } else if (data < current->data) {
                current = current->l;
            } else {
                current = current->r;
            }
        cout << "There is no such element";
        return nullptr;
    }

    static int getsize(Node* nd)
    {
        if( nd== nullptr)
        {return 0;}
        else return nd->s;
    }

    static void SetSize(Node* p) // рекурсивно задать размер дерева
    {
        p->s = getsize(p->l)+getsize(p->r)+1;
    }

    static Node* RightRotation(Node* x)
    {
        Node* y = x->l;
        x->l = y->r;
        y->r = x;
        y->s = x->s;
        SetSize(x);
        return y;
    }

    static Node* LeftRotation(Node* x)
    {
        Node* y = x->r;
        x->r = y->l;
        y->l = x;
        y->s = x->s;
        SetSize(x);
        return y;
    }

    static Node* InsertRoot(Node* p, T data)
    {
        if( p== nullptr )
        {
            Node* nd = new Node;
            nd->s=1;
            nd->data=data;
            nd->r= nullptr;
            nd->l= nullptr;
            return nd;
        }else
            {
        if( data<p->data )
        {
            p->l = InsertRoot(p->l,data);
            return RightRotation(p);
        }
        else
        {
            p->r = InsertRoot(p->r,data);
            return LeftRotation(p);
        }
        }
    }

    static Node* Insert(Node* p, T data)
    {
        if( p== nullptr )
        {
            Node* nd = new Node;
            nd->s=1;
            nd->data=data;
            nd->r= nullptr;
            nd->l= nullptr;
            return nd;
        }
        if( rand()%(p->s+1)==0 )
            return InsertRoot(p,data);
        if( p->data>data )
            p->l = Insert(p->l,data);
        else
            p->r = Insert(p->r,data);
        SetSize(p);
        return p;
    }

    static Node* join(Node* p, Node* q) // объединение двух деревьев
    {
        if( p== nullptr ) return q;
        if( q== nullptr ) return p;
        if(p->s > rand() % (p->s + q->s))
        {
            p->r = join(p->r,q);
            SetSize(p);
            return p;
        }
        else
        {
            q->l = join(p,q->l);
            SetSize(q);
            return q;
        }
    }

    static Node* Deleting(Node* p, int data) // удаление из дерева p первого найденного узла с ключом k
    {
        if( !p ) return p;
        if( p->data==data )
        {
            Node* q = join(p->l,p->r);
            delete p;
            cout << "Element = "<< data << " is deleted" << endl;
            return q;
        }
        else if( data<p->data )
            p->l = remove(p->l,data);
        else
            p->r = remove(p->r,data);
        return p;

    }


};


int main() {
RandomTree tree(50);
for(int i=5; i<105463; i++) {
    tree.Insert(tree.getRoot(), i);

}
    tree.findMaxElement();
    tree.findMinimalElement();
    tree.Deleting(tree.getRoot(), 100);
    tree.findNodeByData(-150);
return 0;
}