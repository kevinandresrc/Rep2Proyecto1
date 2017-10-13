//
// Created by kevin on 11/09/17.
//

#ifndef CONEXIONSERVER_REQUEST_H
#define CONEXIONSERVER_REQUEST_H

#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <string>

class request {
public:
    std::string solicitud;
    std::string key;
    int data;
    int size;

    request();
    request(std::string k, int d, int s, std::string sol);
    request(std::string sol, std::string k);
    request(std::string k, int d, int s);
    ~request();


};


#endif //CONEXIONSERVER_REQUEST_H
