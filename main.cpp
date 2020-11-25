#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "server.h"
#include "client.h"

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
    string name = "pic.png";
    vector<unsigned char> fileBytes(readFile(name));
    //pasteDemo("pic2.png", fileBytes);
    // client newClient;

    int vecSize = fileBytes.size();

    server newServer;
    newServer.turnOn(fileBytes);
    // newClient.turnOn();

    cout << "Hello, World!" << endl;
    return 0;
}
