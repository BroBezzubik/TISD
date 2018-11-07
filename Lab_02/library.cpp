#include "library.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void library::loadBook(Library lib, char *bookData){
    char *ptr = bookData;
    int symCount = 0;
    for (int index = 0; bookData[index] != '\0'; index++){
        symCount++;
        if (bookData[index] == ','){
            char str[20];
            memset(str, '\0', 20);
            strncpy(str, ptr, symCount - 1);
            cout << str << endl;
            ptr = &ptr[symCount];
            symCount = -0;
        } else {

}
    }
    char str[20];
    memset(str, '\0', 20);
    strncpy(str, ptr, symCount);
    cout << str << endl;
    ptr = &ptr[symCount];
    symCount = 0;

}

void library::loadLib(Library lib, char *fileName){
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

