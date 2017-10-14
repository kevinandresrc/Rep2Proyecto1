#include <iostream>
#include "server/server.cpp"
#include "server/file.cpp"
//#include "server/node.cpp"
#include <typeinfo>
#include <thread>
#include <pthread.h>

//PASIVO

int main() {
    setPuerto(9990);
    thread uno(startServer,0);
    uno.join();


    return 0;
}

