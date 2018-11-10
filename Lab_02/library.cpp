#include "library.h"
#include <fstream>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>

void library::loadLib(Library &lib, const char *libFile){
    std::ifstream fstream;
    fstream.open(libFile, std::ios::in);
    if (fstream.is_open()){
        std::string buffer;
        int bookCount = 0;
        while (std::getline(fstream, buffer)){
            if (bookCount < LIBRARY_MAX_SIZE){
            library::Book *book = &lib.books[bookCount];
            library::loadBook(*book, buffer);
            library::Key *key = &lib.keys[bookCount];
            library::loadKey(*book, *key, bookCount);
            bookCount++;
            } else {
                break;
            }
        }
        lib.bookCout = bookCount;
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

void library::loadKey(Book &book, Key &key, int index){
    key.index = index;
    key.page = book.pageCount;
}

void library::loadBook(library::Book &book, const std::string &buffer){
    std::vector<std::string> tokens = library::split(buffer);
    std::strcpy(book.bookName, tokens[0].c_str());
    std::strcpy(book.author, tokens[1].c_str());
    std::strcpy(book.publisher, tokens[2].c_str());
    book.pageCount = std::atoi(tokens[3].c_str());
    book.bookType = (library::BOOK_TYPE) std::atoi(tokens[4].c_str());
    switch (book.bookType) {
        case library::BOOK_TYPE::ART:
            book.type.art.bookType = (library::ART_TYPE) std::atoi(tokens[5].c_str());
            break;
        case library::BOOK_TYPE::TECH:
            book.type.tech.bookType = (library::TECH_TYPE) std::atoi(tokens[5].c_str());
            book.type.tech.year = atoi(tokens[6].c_str());
            break;
        case library::BOOK_TYPE::CHILD:
            book.type.child.bookType = (library::CHILD_TYPE) std::atoi(tokens[5].c_str());
            break;
    }
}

library::OPERATION library::getOperation(){
    for(;;){
        std::cout << "Select Operation:" << std::endl;
        std::cout << "0) EXIT" << std::endl;
        std::cout << "1) Add Book" << std::endl;
        std::cout << "2) Delete Book" << std::endl;
        std::cout << "3) Out put" << std::endl;
        std::cout << "4) Sort" << std::endl;

        int operation = -1;
        std::cout << ">> ";
        std::cin >> operation;

        OPERATION operKey;
        if (operation == 0 || operation == 1 || operation == 2|| operation == 3 ||
                operation == 4){
            return operKey = (OPERATION) operation;
        }
    }
}

std::string library::getBookType(TECH_TYPE type){
    std::string name;
    switch (type) {
    case TECH_TYPE::RUSSIAN:
        name = "RUSSIAN";
        break;
    case TECH_TYPE::TRANSLATED:
        name = "TRANSLATED";
        break;
    default:
        break;
    }
    return name;
}

std::string library::getBookType(ART_TYPE type){
    std::string name;
    switch (type) {
    case ART_TYPE::NOVEL:
        name = "NOVEL";
        break;
    case ART_TYPE::POEM:
        name = "POEM";
        break;
    case ART_TYPE::PLAY:
        name = "PLAY";
        break;
    default:
        break;
    }
    return name;
}

std::string library::getBookType(CHILD_TYPE type){
    std::string name;
    switch (type) {
    case CHILD_TYPE::FAIRY_TAILS:
        name = "FAIRY TAILS";
        break;
    case CHILD_TYPE::CHILD_POEM:
        name = "POEM";
        break;
    default:
        break;
    }
    return name;
}

void library::outPut(Key *keys, int count){
    std::cout << "### TABLE OF KEYS!!! ###" << std::endl;
    for (int index = 0; index < count; index++){
        std::cout.width(3);
        std::cout << index << ")";
        std::cout.width(0);
        std::cout << "Index: ";
        std::cout.width(3);
        std::cout << keys[index].index << '|';
        std::cout.width(0);
        std::cout << "Pages: ";
        std::cout.width(10);
        std::cout << keys[index].page << std::endl;

    }

    std::cout << std::endl;
    std::cout << std::endl;
}

void library::outPut(Book *books, int count){
    std::cout << "### TABLE OF BOOKS!!! ###" << std::endl;
    for (int index = 0; index < count; index++){
        std::cout.width(3);
        std::cout << index << ')';
        std::cout.width(0);
        std::cout << "Book Name: ";
        std::cout.width(20);
        std::cout << std::right << books[index].bookName << '|';
        std::cout.width(0);
        std::cout << "Author: ";
        std::cout.width(20);
        std::cout <<std::right << books[index].author << '|';
        std::cout.width(0);
        std::cout << "Publisher: ";
        std::cout.width(20);
        std::cout <<std::right << books[index].publisher << '|';
        std::cout.width(0);
        std::cout << "Pages: ";
        std::cout.width(10);
        std::cout <<std::right << books[index].pageCount << '|';

        switch (books[index].bookType) {
        case BOOK_TYPE::TECH:
            std::cout.width(0);
            std::cout << "Type: ";
            std::cout.width(10);
            std::cout << getBookType(books[index].type.tech.bookType) << '|';
            std::cout.width(0);
            std::cout << "Year: ";
            std::cout.width(10);
            std::cout << books[index].type.tech.year << '|';
            break;
        case BOOK_TYPE::ART:
            std::cout.width(0);
            std::cout << "Type: ";
            std::cout.width(10);
            std::cout << getBookType(books[index].type.art.bookType) << '|';
            break;
        case BOOK_TYPE::CHILD:
            std::cout.width(0);
            std::cout << "Type: ";
            std::cout.width(10);
            std::cout << getBookType(books[index].type.child.bookType) << '|';
            break;
        default:
            break;
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void library::selectOperation(OPERATION oper, Library &lib, const char *LibFile){
    switch (oper) {
    case OPERATION::EXIT:
        std::exit(0);
        break;
    case OPERATION::ADD:
        break;
    case OPERATION::DELETE:
        break;
    case OPERATION::OUT_PUT:
        library::outPut(lib.books, lib.bookCout);
        library::outPut(lib.keys, lib.bookCout);
        break;
    case OPERATION::SORT:
        break;
    default:
        break;
    }
}


void library::loop(Library &lib, const char *libFile){
    for (;;){
        library::OPERATION operation = getOperation();
       library::selectOperation(operation, lib, libFile);
    }
}
