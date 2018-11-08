#include "library.h"
#include <fstream>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

void library::loadLib(Library &lib, const char *libFile){
    std::ifstream fstream;
    fstream.open(libFile, std::ios::in);
    if (fstream.is_open()){
        std::string buffer;
        while (std::getline(fstream, buffer)){
            library::loadBook(lib.books[lib.bookCout], buffer);
   //         library::loadKey(lib.books[lib.bookCout], lib.keys[lib.bookCout]);
            lib.bookCout++;
        }
    } else {
        throw "Invalid File!!!";
    }
}

std::vector<std::string> library::split(const std::string &str){
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, ',')){
        tokens.push_back(token);
    }
    return tokens;
}

void library::loadBook(library::Book &book, const std::string &buffer){
    std::vector<std::string> tokens = split(buffer);
    char *ptr = book.bookName;
    memset(ptr, 'a', STRING_BUFFER);
    const char *token = tokens[0].c_str();
}
