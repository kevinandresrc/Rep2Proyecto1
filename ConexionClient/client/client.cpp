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

using namespace std;

int puerto;
struct sockaddr_in address;
int sock = 0, valread;
struct sockaddr_in serv_addr;
struct  hostent* server;
//char* hello = "Hello from client";
//char buffer[1024] = {0};
//string ip = "127.0.0.1";

void enviar();

void setPuerto(int p){
    puerto = p;
}

void startClient(){
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return;
    }

    //

    /*
    server = gethostbyname(ip);
    if (server==NULL)
    {
        error("Error opening socket");
        return
    }
    */
    //

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puerto);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        cout<<"Invalid address / Address not supported"<<endl;
        return;
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        cout<<"Connection Failed"<<endl;
        return;
    }
    enviar();
}

void enviar()
{
    request msg("seis", 6, sizeof(4), "add");
    stringstream ss;
    ss << msg;

    write(sock, ss.str().c_str(), sizeof(request));
}

request leer(){
    request a;
    stringstream ss;
    char buf[sizeof(request)];
    string temp;

    read(sock, buf, sizeof(request));
    temp.assign(buf);
    ss << temp;
    ss >> a;
    return a;
}


;