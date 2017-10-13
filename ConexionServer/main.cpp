#include <iostream>
#include "server/server.cpp"
#include <thread>
#include <pthread.h>

int main() {
    setPuerto(9999);
    std::cout << "Hola" << std::endl;
    thread uno(startServer,"pasivo");
    uno.join();


    return 0;
}