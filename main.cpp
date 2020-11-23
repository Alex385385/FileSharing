#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "server.h"

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

int main() {
    //string name = "hello.txt";
    //vector<unsigned char> fileBytes(readFile(name));
    //pasteDemo(name, fileBytes);

    server newServer;
    newServer.turnOn();

    cout << "Hello, World!" << endl;
    return 0;
}
