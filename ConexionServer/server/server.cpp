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

/*

#include <arpa/inet.h>

#include "request.h"*/

using namespace std;

int puerto;
int server_fd, new_socket, valread;
bool activo;
struct sockaddr_in address; //direccion servidor
int opt = 1;
int addrlen = sizeof(address);
char buffer[256];
//char *hello = "Hello from server";

void leer();

void setPuerto(int x){
    puerto = x;
}

void startServer(std::string kind)
{
    if (kind == "activo") {
        activo = true;

    } else {

        activo = false;


        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            std::cout << "Fallo" << endl;
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                       &opt, sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(puerto);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *) &address,
                 sizeof(address)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                                 (socklen_t *) &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        //bzero(buffer,256);

        leer();
        /*
        valread = read( new_socket, buffer, 256);
        printf("%s\n",buffer);
        send(new_socket , hello , strlen(hello) , 0 );
        printf("Hello message sent\n");
        */

    }
}

    void enviar()
    {
        //send(new_socket , hello , strlen(hello) , 0 );
    }

    void leer()
    {
        while(true)
        {

            char buf[sizeof(request)];
            read(new_socket,buf, sizeof(request));
            request *msg = reinterpret_cast<request*>(buf);
            std::cout<< "data: " << msg->data <<endl;
            std::cout<< "size: " << msg->size <<endl;
            std::cout<< "key: " << sizeof(msg->key) <<endl;
            std::cout<< "solicitud: " << msg->solicitud <<endl;


        }


    }
