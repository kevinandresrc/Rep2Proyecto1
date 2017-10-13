#include <iostream>
#include "DS/file.cpp"
#include "DS/node.cpp"
#include <typeinfo>

using namespace std;

int main() {
    int a = 1997;
    file<int> abc(1997,4,"nacimiento");
    struct Node<int>* head = NULL;
    listAppend(&head,abc);
    file<int> cba(2017,4,"actual");
    listAppend(&head,cba);



    printList(head);
    listSearch(head,"actual");
    int act = listSearch(head,"actual").contador;
    int nac = listSearch(head,"nacimiento").contador;

    file<int> aux(2020,4,"graduacion");
    listAppend(&head, aux);

    file<int> aux2(0001,4,"aux2");
    listAppend(&head, aux2);

    printList(head);
    MergeSort(&head);
    printList(head);
    resetAccesos(head);
    listSearch(head, "actual");
    listClear(head);
    printList(head);

    //cout<<listSearch(head,"actual").getData()<<endl;



    //abc.clear();
    //cout<< abc.getKey() <<endl;
    //abc.getData();
    //int x = abc.getData();
    //cout<<"X "<<x<<endl;
    //cout << abc.getData() << endl;
    return 0;
}