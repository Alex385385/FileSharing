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
#include <vector>
#include <pthread.h>
#include <arpa/inet.h>
#include <fcntl.h>


#include "server.h"

#define PORT 8080
//using namespace std;


server::server() = default;
server::~server() = default;

char client_message[2000];
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * socketThread(void *arg){
    int newSocket = *((int *) arg);
    recv(newSocket, client_message, 2000, 0);
    // pthread_mutex_lock(&lock);


    // pthread_mutex_unlock(&lock);
    sleep(1);

}

void server::turnOn(const std::vector<unsigned char> &fileBytes) {
    int createdServer;
    int newSocket;
    long value;

    struct sockaddr_in address;
    int addrlen = sizeof(address);

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

    if(listen(createdServer, 10) < 0) {  //maximum connections allowed is 10
        std::cout << "Error" << std::endl;
        exit(0);
    }

    while(1) {
        std::cout << "Waiting for new connection" << std::endl;
        newSocket = accept(createdServer, (struct sockaddr *)&address, (socklen_t*)&addrlen); // this accepts new incoming connections at createdServer socket
        
        //call the client handler class
        //client handler class will create another thread to handle incoming conenctions


        if(newSocket < 0) {
            std::cout << "Error" << std::endl;
            exit(0);
        }

        char buffer[30000] = {0};
        value = read(newSocket, buffer, 30000);
        printf("%s\n",buffer);

        int fileSize = fileBytes.size();
        int temp = htonl(fileSize);


        //size of file
        write(newSocket, (const char*)&temp, sizeof(temp));
        //sending actual file
        write(newSocket, fileBytes.data(), fileBytes.size());

        std::cout << "Message sent" << std::endl;

        close(newSocket);
    }
}

