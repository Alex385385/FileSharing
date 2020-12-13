//
// Created by Alejandro Millan on 11/27/20.
//
#include <iostream>
#include <string>
#include <sqlite3.h>

#include "login.h"
bool accountExists = false;

login::login() {
    openDB = sqlite3_open("dataBaseLogin.db", &DB);

    if(openDB) {
        std::cout << "Error Opening DB" << std::endl;
        exit(1);
    } else {
        std::cout << "Opening DB" << std::endl;
    }
}

login::~login() = default;

int login::callback(void *NotUsed, int argc, char **argv, char **azColName){
    if(argc == 2) {
        accountExists = true;
        return -1;
    }
    for(int i = 0; i < argc; i++) {

        // Show column name, value, and newline
        std::cout << azColName[i] << ": " << argv[i] << std::endl;

    }

    // Insert a newline
    std::cout << std::endl;

    // Return successful
    return 0;
}

void login::createAccount(const std::string& username, const std::string& password) {
    std::string sql = "INSERT INTO Login ('Username', 'Password') VALUES ('" + username + "', '" + password + "')";

    char *errorMsg = 0;

    openDB = sqlite3_exec(DB, sql.c_str(), callback, 0, &errorMsg);

    if(openDB != 0) {
        std::cerr << "Error Username Exists" << std::endl;
        sqlite3_free(errorMsg);
        return;
    }
    std::cout << "Account created" << std::endl;
}

bool login::loginToAccount(const std::string& username, const std::string& password) {
    std::string sql = "SELECT * FROM Login AS L WHERE L.Username = '" + username + "' AND L.Password = '" + password + "';";

    char *errorMsg = 0;
    std::string data("CALLBACK FUNCTION");

    openDB = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), &errorMsg);

    if(!accountExists) {
        std::cout << "Error No Account Exists" << std::endl;
        return false;
    }
    sqlite3_close(DB);
    return true;
}
