//
// Created by kevin on 14/10/17.
//

#ifndef CONEXIONSERVER_FILE_H
#define CONEXIONSERVER_FILE_H

#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <string>

template <class T>
class file {
private:

    std::string key;
    bool referenciado;

public:
    T* dataPtr;
    T data;
    int size;
    int contador;

    file();

    file(T d, int s, std::string k);

    ~file();

    void setData(T d);

    T& getData();

    int getContador();

    void checkReferenciado();

    bool getReferenciado();

    void clear();

    bool compareKey(std::string other);

    std::string getKey();

    void increaseContador();

    void resetContador();
};


#endif //CONEXIONSERVER_FILE_H
