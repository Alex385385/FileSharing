//
// Created by Alejandro Millan on 11/23/20.
//

#ifndef FILESHARING_CLIENT_H
#define FILESHARING_CLIENT_H


class client {
public:
    client();

    virtual ~client();

    void turnOn();

    void pasteDemo(const std::string& name, const std::vector<unsigned char>& fileBytes);
};


#endif //FILESHARING_CLIENT_H
