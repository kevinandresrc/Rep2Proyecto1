#include <stdio.h>
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
#include <thread>

using namespace std;

int puertoAct = 9991;
int puertoPas = 9990;
struct sockaddr_in address;
int sock = 0, valread;
int sockPas = 0;
int sockAct = 0;
struct sockaddr_in serv_addr;
struct  hostent* server;
string ipA = "127.0.0.1";
string ipP = "127.0.0.1";

void enviar();
int checkActivo();
request leer(int zocket);
void startClientPas();
void startClientAct();
void enviarAux(request msg, int zocket);

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
    //request msg("seis", 6, sizeof(4), "add");
    stringstream ss;
    ss << msg;
    string strmsg = msg.solicitud;
    if (strmsg == "add"){
        write(zocket, ss.str().c_str(), sizeof(request));
    }else if(strmsg == "change"){
        write(zocket, ss.str().c_str(), sizeof(request));
    }else{
        write(zocket, ss.str().c_str(), sizeof(request));
    }

    //write(sock, ss.str().c_str(), sizeof(request));
}

/*
 * @brief Se utiliza cuando se va a ejecutar el get
 * @param el objeto request con lo requerido
 * @return el objeto request con lo solicitado
 */
request enviarYrecibir(request msg){
    if (checkActivo() == 0){
        msg.data = 0;
        msg.size = 0;
        stringstream ss;
        ss << msg;
        string strmsg = msg.solicitud;
        if (strmsg == "get"){
            write(sockPas, ss.str().c_str(), sizeof(request));
            return leer(sockPas);
        }
    }else{
        msg.data = 0;
        msg.size = 0;
        stringstream ss;
        ss << msg;
        string strmsg = msg.solicitud;
        if (strmsg == "get"){
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
     */

    /*
    read(sock, buf, sizeof(request));
    temp.assign(buf);
    ss << temp;
    ss >> a;
    return a;
     */
}


;