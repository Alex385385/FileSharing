#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "server.h"
#include "client.h"
#include "login.h"

using namespace std;

vector<unsigned char> readFile(const string& fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ios::binary);

    if (!inputFile.is_open()) {
        cout << "Error Opening File" << endl;
        exit(0);
    }

    vector<unsigned char>bytes((istreambuf_iterator<char>(inputFile)), {});

    inputFile.close();
    return bytes;
}

void pasteDemo(const string& name, const vector<unsigned char>& fileBytes) {
    ofstream output( name, ios::binary);

    for(unsigned char fileByte : fileBytes) {
        output.put(fileByte);
    }

    output.close();
}

void menu() {
    login loginToDB;
    int input;
    bool in = false;

    string username;
    string password;
    string fileName;

    cout << "Welcome to File Sharing" << endl;

    do {
        cout << "1) Login" << endl;
        cout << "2) Create Account" << endl;
        cin >> input;

        while(!cin) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "1) Login" << endl;
            cout << "2) Create Account" << endl;
            cin >> input;
        }

        if(input == 1) {
            cout << "Username: ";
            cin >> username;
            cout << endl;

            cout << "Password: ";
            cin >> password;
            cout << endl;

            in = loginToDB.loginToAccount(username, password);
        } else if(input == 2) {
            cout << "Enter Username: ";
            cin >> username;
            cout << endl;

            cout << "Enter Password: ";
            cin >> password;
            cout << endl;

            loginToDB.createAccount(username, password);
        }
    } while (!in);

    cout << "1) Send File" << endl;
    cout << "2) Recieve File" << endl;
    cin >> input;

    while(!cin) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "1) Send File" << endl;
        cout << "2) Recieve File" << endl;
        cin >> input;
    }

    if(input == 1) {
        server newServer;
        cout << "Type file name to send: ";
        cin >> fileName;
        cout << endl;

        vector<unsigned char> fileBytes(readFile(fileName));
        newServer.turnOn(fileBytes);

    } else if(input == 2) {
        client newClient;
        newClient.turnOn();
    }

}

int main() {
    string name = "pic.png";
    vector<unsigned char> fileBytes(readFile(name));
    //pasteDemo("pic2.png", fileBytes);
    // client newClient;

    //int vecSize = fileBytes.size();

    server newServer;
    newServer.turnOn(fileBytes);
    // newClient.turnOn();

    //login log;
    //log.loginToAccount("al", "1234");
    //log.createAccount("aldio", "1236");

    cout << "Hello, World!" << endl;
    return 0;
}
