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

    /*
    send(sock, hello, strlen(hello), 0);
    cout<<"Hello message sent"<<endl;
    valread = read(sock, buffer, 1024);
    printf("%s\n",buffer);
     */
}

void enviar()
{
    request msg("cuatro", 5, sizeof(4), "add");
    char* tmp = reinterpret_cast<char *>(&msg);
    send(sock,tmp, sizeof(request),0);
};