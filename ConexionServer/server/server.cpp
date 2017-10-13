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
#include <sstream>

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

    void enviar(request rq, int s)
    {
        stringstream ss;
        ss << rq;

        write(s, ss.str().c_str(), sizeof(request));
    }

    void leer()
    {
        while(true)
        {

            request a;
            stringstream ss;
            char buf[sizeof(request)];
            string temp;

            read(new_socket, buf, sizeof(request));
            temp.assign(buf);
            ss << temp;
            ss >> a;
            cout<<a.size<<endl;
            cout<<a.data<<endl;
            cout<<a.key<<endl;
            cout<<a.solicitud<<endl;
            break;

        }


    }
