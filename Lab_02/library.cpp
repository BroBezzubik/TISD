#include "library.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(const string &s, char delimeter){
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimeter)){
        tokens.push_back(token);
    }
    return tokens;
}

void library::loadBook(Library &lib, char *bookData){
    string data = bookData;
    vector<string> tokens = split(data, ',');
    library::Book *book = &lib.table[lib.count];
    memset(book->bookName,'a', BUFFER_SIZE);
    cout << book->bookName << endl;
}

void library::loadLib(Library &lib, char *fileName){
    ifstream dataStream;
    dataStream.open(fileName, ios::in);
    if (dataStream.is_open()){
        char buffer[STRING_BUFFER];
        while (dataStream.getline(buffer, STRING_BUFFER, '\n')){
            library::loadBook(lib, buffer);
        }
    } else {
        throw "Invalid File!!!";
    }
}

void library::updateKeyTable(Library &lib, keyTable &table){
}

void library::loop(library::Library &lib, library::keyTable &key){
}

