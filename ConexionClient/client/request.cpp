//
// Created by kevin on 11/09/17.
//

#include "request.h"
#include <string>

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