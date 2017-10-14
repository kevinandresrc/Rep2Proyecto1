///
// Created by kevin on 13/10/17.
//

#include "rmlib.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include "request.h"
#include <string>
#include <sstream>



int checkActivo();
request leer(int zocket);
void startClientPas();
void startClientAct();
void enviarAux(request msg, int zocket);
void setIpA(string a);
void setIpP(string a);
void setPuertoAct(int p);
void setPuertoPas(int p);
void empezar();
void enviar(request msg);
request enviarYrecibir(request msg);

using namespace std;

int puertoAct = 9991;
int puertoPas = 9990;
//struct sockaddr_in address;
//int valread;
int sockPas = 0;
int sockAct = 0;
struct sockaddr_in serv_addr;
struct  hostent* server;
string ipA = "127.0.0.1";
string ipP = "127.0.0.1";
bool conectadoPas = false;
bool conectadoAct = false;


/*
 * @brief constructor nulo
 */
rmlib::rmlib() {
    value = -1;
    value_size = -1;
    key = "sin valor";
    inicializado = false;
    bloqueado = false;
}

/*
 * @brief destructor
 */
rmlib::~rmlib() {

}

/*
 * @brief constructor PRIVADO
 * @param String k el key
 * @param int v el valor
 * @param int vz el tamano del valor
 */
rmlib::rmlib(string k, int v, int vz) {
    key = k;
    value = v;
    value_size = vz;
    bloqueado = false;
    inicializado = true;
}

/*
 * @brief se conecta con los servidores
 * @param String ip direccion IP del Servidor Activo
 * @param int port puerto del Servidor Activo
 * @param String ipHA direccion IP del Servidor Pasivo
 * @param int portHA puerto del Servidor Pasivo
 */
void rmlib::rm_init(string ip, int port, string ipHA, int portHA) {
    if (port==portHA && ip==ipHA){
        bloqueado = true;
        inicializado = false;
    }else{
        inicializado = false;
        setPuertoAct(port);
        setPuertoPas(portHA);
        setIpA(ip);
        setIpP(ipHA);
        empezar();
        if(conectadoAct==true && conectadoPas== true){
            inicializado = true;
            bloqueado = false;
        }else{
            inicializado = false;
            bloqueado = true;
        }

    }
}

/*
 * @brief agrega un nuevo elemento a la memoria remota
 * @param Key el string con la key asignada
 * @param *Value el puntero al dato a guardar
 * @param Value_size valor en int del dato a guardar
 * @return imprime en pantalla como haya sido ejecutada la operacion
 */
void rmlib::rm_new(string Key, int *Value, int Value_size) {
    if(sizeof(*Value)==Value_size && bloqueado== false) {
        value = *Value;
        key = Key;
        value_size = Value_size;
        request a(key, value, value_size, "add");
        request answer = enviarYrecibir(a);
        if(answer.solicitud == "ok"){
            cout<< "Se ha agregado correctame: " << value << " con la key: " << key <<endl;
        }else{
            cout<< "La llave ingresada ya esta en uso"<<endl;
        }
    }else{
        cout<< "Error al agregar a la memoria remota"<<endl;
    }
}

/*
 * @brief obtiene un archivo de la memoria externa
 * @param un String con el key del archivo
 * @return un objeto tipo rmlib, si se da el caso imprime en pantalla el error
 * y devuelve un objeto rmlib "basura"
 */
rmlib rmlib::rm_get(string key) {
    request a(key,0,0,"get");
    request answer = enviarYrecibir(a);
    if(answer.solicitud == "ok"){
        return rmlib(answer.key,answer.data, answer.size);
    }else{
        cout<<"Error al obtener el archivo de memoria"<<endl;
        return rmlib("Error", -1, -1);
    }
}

/*
 * @brief elimina un elemento de la memoria externa
 * @param un puntero a un objeto rmlib
 * @return Muestra en pantalla si hubiera un error
 */
void rmlib::rm_delete(rmlib *file) {
    if(bloqueado== false && inicializado == true){
        rmlib x = *file;
        request a(x.key, x.value, x.value_size, "delete");
        enviar(a);
    }else{
        cout<<"Error al eliminar"<<endl;
    }
}









//Logic ======= conexion con Server


/*
 * @brief fija el IP del server Activo
 * @param string con la ip dada
 */
void setIpA(string a){
    ipA = a;
}

/*
 * @brief fija el IP del server Pasivo
 * @param string con la ip dada
 */
void setIpP(string a){
    ipP = a;
}

/*
 * @brief fija el puerto del server Activo
 * @param int con el numero de puerto
 */
void setPuertoAct(int p){
    puertoAct = p;
}

/*
 * @brief fija el puerto del server Pasivo
 * @param int con el numero de puerto
 */
void setPuertoPas(int p){
    puertoPas = p;
}

/*
 * @brief Empieza la conexion con los servers
 */
void empezar(){
    startClientPas();
    startClientAct();
}

/*
 * @brief Empieza conexion con server Pasivo
 */
void startClientPas(){
    if ((sockPas = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return;
    }


    //
    server = gethostbyname(ipP.c_str());
    if (server==NULL)
    {
        cout<<("Error opening socket")<<endl;
        return;
    }
    //


    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puertoPas);
    if(inet_pton(AF_INET, ipP.c_str(), &serv_addr.sin_addr)<=0)
    {
        cout<<"Invalid address / Address not supported"<<endl;
        return;
    }
    if (connect(sockPas, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        cout<<"Connection Failed"<<endl;
        return;
    }

    conectadoPas = true;
}

/*
 * @brief empieza conexion con server Activo
 *
 */
void startClientAct(){
    if ((sockAct = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return;
    }


    //
    server = gethostbyname(ipA.c_str());
    if (server==NULL)
    {
        cout<<("Error opening socket")<<endl;
        return;
    }
    //



    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puertoAct);
    if(inet_pton(AF_INET, ipA.c_str(), &serv_addr.sin_addr)<=0)
    {
        cout<<"Invalid address / Address not supported"<<endl;
        return;
    }
    if (connect(sockAct, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        cout<<"Connection Failed"<<endl;
        return;
    }

    conectadoAct = true;
}

/*
 * @brief metodo para verificar si se puede conectar al server Activo
 * @return devuelve 0, si el servidor no esta disponible; caso contrario devuelve 1
 */
int checkActivo(){
    if ((sockAct = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return 0;
    }


    //
    server = gethostbyname(ipA.c_str());
    if (server==NULL)
    {
        cout<<("Error opening socket")<<endl;
        return 0;
    }
    //



    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puertoAct);
    if(inet_pton(AF_INET, ipA.c_str(), &serv_addr.sin_addr)<=0)
    {
        cout<<"Invalid address / Address not supported"<<endl;
        return 0;
    }
    if (connect(sockAct, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        cout<<"Connection Failed"<<endl;
        return 0;
    }
    return 1;
}

/*
 * @brief Metodo para enviar una solicitud al server, que no implica recibir datos
 * @param objecto request con la solicitud
 */
void enviar(request msg){
    if(checkActivo() == 0){
        enviarAux(msg, sockPas);
    }else{
        enviarAux(msg, sockAct);
        enviarAux(msg, sockPas);
    }
}

/*
 * @brief Metodo para enviar al server Aux, se utiliza para cuando se usa delete, add, change
 * @param objeto request con lo requerido segun la solicitud
 */
void enviarAux(request msg, int zocket)
{
    stringstream ss;
    ss << msg;
    write(zocket, ss.str().c_str(), sizeof(request));
}

/*
 * @brief Se utiliza cuando se va a ejecutar el get
 * @param el objeto request con lo requerido
 * @return el objeto request con lo solicitado
 */
request enviarYrecibir(request msg){
    if(msg.solicitud == "get") {
        if (checkActivo() == 0) {
            msg.data = 0;
            msg.size = 0;
            stringstream ss;
            ss << msg;
            write(sockPas, ss.str().c_str(), sizeof(request));
            return leer(sockPas);
        } else {
            msg.data = 0;
            msg.size = 0;
            stringstream ss;
            ss << msg;
            write(sockPas, ss.str().c_str(), sizeof(request));
            write(sockAct, ss.str().c_str(), sizeof(request));
            request Pas = leer(sockPas);
            request Act = leer(sockAct);
            return Pas;
        }
    }else{
        if (checkActivo() == 0) {
            stringstream ss;
            ss << msg;
            write(sockPas, ss.str().c_str(), sizeof(request));
            return leer(sockPas);
        } else {
            stringstream ss;
            ss << msg;
            write(sockPas, ss.str().c_str(), sizeof(request));
            write(sockAct, ss.str().c_str(), sizeof(request));
            request Pas = leer(sockPas);
            request Act = leer(sockAct);
            return Pas;
        }
    }
}

/*
 * @brief Metodo para esperar una respuesta del server, solo se usa cuando se utiliza el get
 * @return objecto request obtenido del server
 */
request leer(int zocket){

    request a;
    stringstream ss;
    char buf[sizeof(request)];
    string temp;
    read(zocket, buf, sizeof(request));
    cout<<"entra"<<endl;
    temp.assign(buf);
    cout<<"temp: "<<temp<<endl;
    ss << temp;
    ss >> a;
    return a;

    /*
    while(true){
        cout<<"entra"<<endl;
        try {
            read(zocket, buf, sizeof(request));
            cout<<"entra"<<endl;
            temp.assign(buf);
            cout<<"temp: "<<temp<<endl;
            ss << temp;
            ss >> a;
            return a;
        }catch (int e){
            cout << "entra AUX"<<endl;
        }

    }

    read(sock, buf, sizeof(request));
    temp.assign(buf);
    ss << temp;
    ss >> a;
    return a;
     */
}