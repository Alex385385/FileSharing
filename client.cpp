//
// Created by Alejandro Millan on 11/23/20.
//
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

#include "client.h"

#define PORT 8080

client::client() = default;
client::~client() = default;

void client::turnOn() {
    int clientSocket = 0;
    long value;
    struct  sockaddr_in serverAddress;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(clientSocket < 0) {
        std::cout << "Error" << std::endl;
        exit(0);
    }

    memset(&serverAddress, '0', sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cout << "Invalid address" << std::endl;
        exit(0);
    }

    if(connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        exit(0);
    }

    send(clientSocket, hello, strlen(hello), 0 );
    std::cout << "Hello message sent" << std::endl;
    value = read(clientSocket , buffer, 1024);
    printf("%s\n",buffer );
    return;
}