//
// Created by kevin on 11/09/17.
//

#ifndef CONEXIONCLIENT_REQUEST_H
#define CONEXIONCLIENT_REQUEST_H

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


#endif //CONEXIONCLIENT_REQUEST_H
