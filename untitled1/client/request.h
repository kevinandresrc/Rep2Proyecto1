//
// Created by kevin on 14/10/17.
//

#ifndef UNTITLED1_REQUEST_H
#define UNTITLED1_REQUEST_H

#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <string>
#include <strstream>

using namespace std;


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

    friend ostream& operator<< (ostream& out, request& object){
        out<< object.solicitud << " " << object.key << " " << object.data << " " << object.size;
        return out;
    }
    friend istream& operator>> (istream& in, request& object){
        in >> object.solicitud;
        in >> object.key;
        in >> object.data;
        in >> object.size;
        return in;
    }

};


#endif //UNTITLED1_REQUEST_H
