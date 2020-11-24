//
// Created by Alejandro Millan on 11/22/20.
//

#ifndef FILESHARING_SERVER_H
#define FILESHARING_SERVER_H

#include <vector>

class server {
public:
    server();

    virtual ~server();

    void turnOn(const std::vector<unsigned char> &fileBytes);

};


#endif //FILESHARING_SERVER_H
