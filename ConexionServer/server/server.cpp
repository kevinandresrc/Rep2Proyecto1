#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <thread>
#include "request.h"
#include "node.cpp"
#include <sstream>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread>



using namespace std;


int puerto = 0;
int server_fd, new_socket, valread;
bool activo;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
struct sockaddr_in serv_addr;
struct  hostent* server;
int contador = 0;

int puertoActivo = 9991;
string ipActivo = "127.0.0.1";
int socketServerActivo;
int socketServerPasivo;

bool Activo_is_dead = false;
bool actualizando = false;
bool flagStop = false;
bool Activo_was_dead = false;

struct Node<int>* head = NULL;

void setPuertoActivo(int x);
void setIpActivo(string l);
void setPuerto(int x);
void startServer(int kind);
void pausarActivo();
void encenderActivo();
void enviar(request rq, int s);
void interpretar(request a, int socket);
void startServerPas();
void startServerAct();
void leer(int socket);
void connectPasivo();
void checkActivo();
int checkActivoAux();
void ActualizarActivo();
void Eficaz();
void EXIT();

/*
 * @brief fija el puerto del servidor activo, el cual lo va a requerir el servidor pasivo
 * @param x el puerto del servidor pasivo
 */
void setPuertoActivo(int x){
    puertoActivo = x;
}

/*
 * @brief fija el ip del servidor activo, el cual lo va a requerir el servidor pasivo
 * @param l el ip del servidor pasivo
 */
void setIpActivo(string l){
    ipActivo = l;
}

/*
 * @brief fija el puerto a trabajar el server
 * @param int X el numero de puerto
 */
void setPuerto(int x){
    puerto = x;
}

/*
 * @brief revisa cual de los 2 servers se va a ejecutar y llama a la funcion
 * @param kind es un int, es 1 si el servidor sera activo y 0 si este sera pasivo
 */
void startServer(int kind) {
    if (kind == 1) {
        activo = true;
        if(puerto==0){
            setPuerto(9991);
            startServerAct();
        }else {
            startServerAct();
        }
    } else {
        activo = false;
        if(puerto==0){
            setPuerto(9990);
            startServerPas();
        }else {
            startServerPas();
        }
    }
}

/*
 * @brief inicializa el servidor activo
 */
void startServerAct(){
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        cout << "Fallo" << endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        cout<<"Error setsockopt"<<endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(puerto);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        cout<<"Error bind"<<endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 100) < 0) {
        cout<<"Error listen"<<endl;
        exit(EXIT_FAILURE);
    }

    if ((socketServerPasivo = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        cout<<"Error accept"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Server Pasivo se ha hecho presente"<<endl;
    thread uno(leer, socketServerPasivo);
    uno.detach();
    //leer(socketServerPasivo);
    while(true){
        if(Activo_is_dead){

        }else {
            int x;
            if ((x = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                cout << "Error accept" << endl;
                exit(EXIT_FAILURE);
            }
            new_socket = x;
            cout << "Nuevo cliente" << endl;
            //leer(new_socket);
            thread dos(leer, new_socket);
            dos.detach();
        }
    }

}

/*
 * @brief Pausa el servidor Activo, para simular que ha muerto
 */
void pausarActivo(){
    flagStop = true;
}

/*
 * @brief Enciende el servidor Activo, para simular que ha regresado
 */
void encenderActivo(){
    flagStop = false;
    thread uno(leer, socketServerPasivo);
    uno.detach();
    //leer(socketServerPasivo);
}

/*
 * @brief Se conecta al servidor activo como un nuevo cliente de este
 */
void connectPasivo(){
    if ((socketServerActivo = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return;
    }

    //
    server = gethostbyname(ipActivo.c_str());
    if (server==NULL)
    {
        cout<<("Error opening socket")<<endl;
        return;
    }
    //


    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puertoActivo);
    if(inet_pton(AF_INET, ipActivo.c_str(), &serv_addr.sin_addr)<=0)
    {
        cout<<"Invalid address / Address not supported"<<endl;
        return;
    }
    if (connect(socketServerActivo, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        cout<<"Connection Failed"<<endl;
        return;
    }
    cout<<"Se ha efectuado la conexion con el servidor activo"<<endl;
}

/*
 * @brief inicializa el servidor Pasivo
 */
void startServerPas(){
    connectPasivo();

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        cout << "Fallo" << endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        cout<<"Error setsockopt"<<endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(puerto);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        cout<<"Error bind"<<endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 100) < 0) {
        cout<<"Error listen"<<endl;
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        cout<<"Error accept"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Nuevo Cliente"<<endl;
    thread uno(leer, new_socket);
    uno.join();
    //leer(new_socket);
}

/*
 * @brief Envia el objeto solicitado o el error segun sea lo que se haya solicitado
 * @param rq el objeto request a enviar
 * @param s el int del socket al que se va a enviar el objeto
 */
void enviar(request rq, int s) {
    stringstream ss;
    ss << rq;
    write(s, ss.str().c_str(), sizeof(request));
}

/*
 * @brief escucha en el socket en busqueda de mensajes
 * @param int socket el socket en el cual va a escuchar esperando mensajes
 */
void leer(int socket) {
    request b("",1,1,"");
    while(!flagStop) {
        request a;
        stringstream ss;
        char buf[sizeof(request)];
        string temp;
        read(new_socket, buf, sizeof(request));
        temp.assign(buf);
        ss << temp;
        ss >> a;
        if(a.data!=-1 && a.data!=b.data && a.key!=b.key) {
            cout << "size " << a.size << endl;
            cout << "data " << a.data << endl;
            cout << "key " << a.key << endl;
            cout << "solicitud " << a.solicitud << endl;
            b.solicitud = a.solicitud;
            b.key = a.key;
            b.data = a.data;
            interpretar(a, new_socket);
            Eficaz();
            printList(head);
        }else{
            Eficaz();
        }
    }
}

/*
 * @brief Revisa el estado del server Activo
 */
void Eficaz(){
    checkActivo();
    if(Activo_is_dead){
        Activo_was_dead = true;
    }
    else{
        if(Activo_was_dead){
            Activo_was_dead = false;
            resetAccesos(head);
            ActualizarActivo();
            resetAccesos(head);
        }
    }
}

/*
 * @brief Le envia al Server Activo la lista de memoria
 */
void ActualizarActivo(){
    int x = 0;
    while (x!=(listSize(head)-1)){
        file<int> aux = listGet(head,x);
        request a(aux.getKey(), aux.data, aux.size, "actualizar");
        enviar(a, socketServerActivo);
        x++;
    }

    file<int> aux = listGet(head,x);
    request a(aux.getKey(), aux.data, aux.size, "factualizar");
    enviar(a, socketServerActivo);
}

/*
 * @brief interpreta el mensaje en el objeto recibido por sockets
 * @param objeto request recibido por sockets
 * @param int socket de quien ha enviado el objeto
 */
void interpretar(request a, int socket){
    string sol = a.solicitud;
    if(sol == "add"){
        if(listContain(head,a.key)){
            request aux("",-1,0,"Error");
            enviar(aux, socket);
        }else{
            file<int> aux(a.data,a.size,a.key);
            listAppend(&head,aux);
            request aux2("",-1,0,"ok");
            enviar(aux2, socket);
        }
    }else if(sol == "delete"){
        if(listContain(head, a.key)){
            listDelete(&head,a.key);
        }
    }else if(sol == "get"){
        if(listContain(head, a.key)){
            file<int> aux = listSearch(head, a.key);
            request aux2(aux.getKey(), aux.getData(), aux.size, "ok");
            cout << "data "<< aux2.data<<endl;
            contador++;
            if(contador==10){
                listClear(head);
                MergeSort(&head);
                contador = 0;
                enviar(aux2, socket);
            }else {
                enviar(aux2, socket);
            }
        }else{
            request aux2("", -1, 0, "Error");
            enviar(aux2, socket);
        }
    }else if(sol == "change"){
        if(listContain(head, a.key)){
            listChange(head,a.key,a.data);
            contador++;
            if(contador==10){
                listClear(head);
                MergeSort(&head);
                contador = 0;
            }else {
            }
        }
    }else if(sol == "actualizar"){
        if(actualizando == false){
            listReset(head);
            actualizando = true;
            file<int> aux(a.data, a.size, a.key);
            listAppend(&head,aux);
        }else{
            file<int> aux(a.data, a.size, a.key);
            listAppend(&head,aux);
        }
    }else if(sol == "factualizar"){
        actualizando = false;
        file<int> aux(a.data, a.size, a.key);
        listAppend(&head,aux);
        flagStop = false;
    }
}

/*
 * @brief Revisa si se encuentra en el server Pasivo para verificar el estado del server Activo
 */
void checkActivo(){
    if(activo){
    }else{
        /*
        int x = checkActivoAux();
        if(x==1){
            Activo_is_dead = false;
        }else{
            Activo_is_dead = true;
        }*/


        int err = 0;
        socklen_t size = sizeof (err);
        int check = getsockopt (socketServerActivo, SOL_SOCKET, SO_ERROR, &err, &size);
        if (check != 0)
        {
            Activo_is_dead = true;
        }
        Activo_is_dead = false;
    }
}

/*
 * @brief metodo para verificar si se puede conectar al server Activo
 * @return devuelve 0, si el servidor no esta disponible; caso contrario devuelve 1
 */
int checkActivoAux(){
    int y;
    if ((y = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return 0;
    }


    //
    server = gethostbyname(ipActivo.c_str());
    if (server==NULL)
    {
        cout<<("Error opening socket")<<endl;
        return 0;
    }
    //


    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puertoActivo);
    if(inet_pton(AF_INET, ipActivo.c_str(), &serv_addr.sin_addr)<=0)
    {
        cout<<"Invalid address / Address not supported"<<endl;
        return 0;
    }
    if (connect(y, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        cout<<"Connection Failed"<<endl;
        return 0;
    }
    return 1;
}

/*
 * Metodo para salir y dejar de estar escuchando en los sockets
 */
void EXIT(){
    flagStop = true;
}