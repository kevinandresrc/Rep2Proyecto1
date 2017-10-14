//
// Created by kevin on 14/10/17.
//

#ifndef UNTITLED1_RMLIB_H
#define UNTITLED1_RMLIB_H

#include <string>

using namespace std;

class rmlib {
public:
    int value;
    int value_size;
    string key;

    rmlib();
    ~rmlib();

    void rm_init(string ip, int port, string ipHA, int portHA);
    void rm_new(string key, int* value, int value_size);
    rmlib rm_get(string key);
    void rm_delete(rmlib* file);

private:
    bool bloqueado;
    bool inicializado;

    rmlib(string k, int v, int vz);
};


#endif //UNTITLED1_RMLIB_H
