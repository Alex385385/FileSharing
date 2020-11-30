//
// Created by Alejandro Millan on 11/27/20.
//

#ifndef FILESHARING_LOGIN_H
#define FILESHARING_LOGIN_H

#include <iostream>
#include <sqlite3.h>

class login {
private:
    sqlite3* DB;
    int openDB = 0;
    //bool accountExists = true;
public:
    login();

    virtual ~login();

    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

    void createAccount(const std::string& username, const std::string& password);

    bool loginToAccount(const std::string& username, const std::string& password);

};


#endif //FILESHARING_LOGIN_H
