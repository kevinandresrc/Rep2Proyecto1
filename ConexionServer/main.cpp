#include <iostream>
#include "server/server.cpp"
#include "server/file.cpp"
//#include "server/node.cpp"
#include <typeinfo>
#include <thread>
#include <pthread.h>



int main() {
    setPuerto(9990);
    std::cout << "Hola" << std::endl;
    thread uno(startServer,0);
    uno.join();


    return 0;
}

/*
 *
 *
int ayuda(){
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
 */
