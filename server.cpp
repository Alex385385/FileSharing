//
// Created by Alejandro Millan on 11/22/20.
//
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#include "server.h"

#define PORT 8080
//using namespace std;


server::server() = default;
server::~server() = default;

void server::turnOn() {
    int createdServer;
    int newSocket;
    long value;

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *hello = "Hello from client";

    createdServer = socket(AF_INET, SOCK_STREAM, 0);

    if(createdServer == 0) {
        std::cout << "Error" << std::endl;
        exit(0);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if(bind(createdServer, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cout << "Error" << std::endl;
        exit(0);
    }

    if(listen(createdServer, 10) < 0) {
        std::cout << "Error" << std::endl;
        exit(0);
    }

    while(1) {
        std::cout << "Waiting for new connection" << std::endl;
        newSocket = accept(createdServer, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        if(newSocket < 0) {
            std::cout << "Error" << std::endl;
            exit(0);
        }

        char buffer[30000] = {0};
        value = read(newSocket, buffer, 30000);
        printf("%s\n",buffer);
        write(newSocket, hello, strlen(hello));
        std::cout << "Message sent" << std::endl;

        close(newSocket);
    }
}