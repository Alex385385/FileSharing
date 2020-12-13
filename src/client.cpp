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
#include <fstream>
//#include <string>
#include <algorithm>
#include <vector>

#include "client.h"

#define PORT 8080

client::client() = default;
client::~client() = default;

void client::pasteDemo(const std::string& name, const std::vector<unsigned char>& fileBytes) {
    std::ofstream output( name, std::ios::binary);

    for(unsigned char fileByte : fileBytes) {
        output.put(fileByte);
    }

    output.close();
}

void client::turnOn() {
    int clientSocket = 0;
    long value;
    long value2;
    struct  sockaddr_in serverAddress;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    std::string fileName;

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

    int fileSize;
    int fileSizeConverted;

    //read file size
    value2 = read(clientSocket, &fileSize, 4);
    fileSizeConverted = ntohl(fileSize);

    std::vector<unsigned char> buf(fileSizeConverted);

    //get file
    value = read(clientSocket , &buf[0], fileSizeConverted);

    //read file name
    char buffer2[1024] = {0};
    value = read(clientSocket, buffer2, 1024);
    printf("%s\n",buffer2);
    std::string str(buffer2);

    close(clientSocket);

    pasteDemo(str, buf);
}