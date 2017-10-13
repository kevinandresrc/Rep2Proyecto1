//
// Created by kevin on 11/09/17.
//

#include "request.h"

using namespace std;

/*
 * @brief constructor nulo
 */
request::request() {
    solicitud = "";
    key = "";
    data = -1;
    size = 0;
}

/*
 * @brief constructor
 * @param sol solitud por hacer
 * @param k key del data
 */
request::request(std::string sol, std::string k) {
    solicitud = sol;
    key = k;
    data = -1;
    size = 0;
}

/*
 * @brief constructor
 * @param k key del data
 * @param d int del dato
 * @param s int del size del dato
 */
request::request(std::string k, int d, int s) {
    key = k;
    data = d;
    size = s;
    solicitud = "";
}

/*
 * @brief constructor
 * @param k key del dato
 * @param d int del dato
 * @param s size del dato
 * @param sol solicitud por hacer
 */
request::request(std::string k, int d, int s, std::string sol) {
    key = k;
    data = d;
    size = s;
    solicitud = sol;
}

/*
 * @brief destructor
 */
request::~request() {

}

/*
 *@brief selializador
 *@param  &out
 *@param &object
 * @return
 *

friend ostream& request::operator<<(ostream &out, request &object) {
    out<< object.solicitud << " " << object.key << " " << object.data << " " << object.size;
    return out;
}

friend istream& request::operator>>(istream &in, request &object) {
    in >> object.solicitud;
    in >> object.key;
    in >> object.data;
    in >> object.size;
    return in;
}
 */