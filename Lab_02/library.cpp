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


void library::addBook(Library &lib, const char *libFile){
    try{
        char bookName[STRING_BUFFER_UINPUT];
        std::cout << "Book name: ";
        std::cin >> bookName;
        if (strlen(bookName) > STRING_BUFFER){ throw "Name is to big!";}


        char autor[STRING_BUFFER_UINPUT];
        std::cout << "Author: ";
        std::cin >> autor;
        if (strlen(autor) > STRING_BUFFER){ throw "Author name is to big!";}

        char publisher[STRING_BUFFER_UINPUT];
        std::cout << "Publisher: ";
        std::cin >> publisher;
        if (strlen(publisher) > STRING_BUFFER){ throw "Publisher is to long!";}

        int pages = 0;
        std::cout << "Pages: ";
        std::cin >> pages;
        if (pages > 99999 && pages < 0){ throw "Wrong page count!";}

        int type = 0;
        std::cout << "0)Tech" << std::endl;
        std::cout << "1)Art" << std::endl;
        std::cout << "2)Child" << std::endl;
        std::cout << "Type: " << std::endl;
        std::cin >> type;

        library::Book *book = &lib.books[lib.bookCout];
        switch (type) {
        case BOOK_TYPE::TECH:
            std::cout << "You selected Tech type!" << std::endl;

            int year;
            std::cout << "Input year: ";
            std::cin >> year;
            if (year < 0 && year > 2020){ throw "Invalid year!";}

            int tech_type;
            std::cout << "0)Russian" << std::endl;
            std::cout << "1)Translated" << std::endl;
            std::cout << "Input book type: ";
            std::cin >> tech_type;
            if (type != TECH_TYPE::RUSSIAN && type != TECH_TYPE::TRANSLATED){
                throw "Invlid tech type!";
            }

            book->type.tech.bookType = (TECH_TYPE) tech_type;
            book->type.tech.year = year;

            break;
        case BOOK_TYPE::ART:
            std::cout << "You selected Art type: ";

            int artType;
            std::cout << "0)Novel" << std::endl;
            std::cout << "1)Play" << std::endl;
            std::cout << "2)Poem" << std::endl;
            std::cout << "Input book type: ";
            std::cin >> artType;
            if (artType != ART_TYPE::NOVEL && artType != ART_TYPE::PLAY && artType != ART_TYPE::POEM){
                throw "Invalid type!";
            }

            book->type.art.bookType = (ART_TYPE) artType;
            break;
        case BOOK_TYPE::CHILD:
            //todo Довавить доволнение детской книги
            break;
        default:
            throw "Invalid book type!";
            break;
        }

        strcpy(book->author, autor);
        strcpy(book->bookName, bookName);
        strcpy(book->publisher, publisher);
        book->pageCount = pages;
        book->bookType = (BOOK_TYPE) type;
        library::loadKey(*book, lib.keys[lib.bookCout], lib.bookCout);
        lib.bookCout++;
    } catch (const char *msg){
        std::cerr << msg << std::endl;
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

void library::outPutBook(Book &book, int index){
    std::cout.width(3);
    std::cout << index << ')';
    std::cout.width(0);
    std::cout << "Book Name: ";
    std::cout.width(20);
    std::cout << std::right << book.bookName << '|';
    std::cout.width(0);
    std::cout << "Author: ";
    std::cout.width(20);
    std::cout <<std::right << book.author << '|';
    std::cout.width(0);
    std::cout << "Publisher: ";
    std::cout.width(20);
    std::cout <<std::right << book.publisher << '|';
    std::cout.width(0);
    std::cout << "Pages: ";
    std::cout.width(10);
    std::cout <<std::right << book.pageCount << '|';

    switch (book.bookType) {
    case BOOK_TYPE::TECH:
        std::cout.width(0);
        std::cout << "Type: ";
        std::cout.width(10);
        std::cout << getBookType(book.type.tech.bookType) << '|';
        std::cout.width(0);
        std::cout << "Year: ";
        std::cout.width(10);
        std::cout << book.type.tech.year << '|';
        break;
    case BOOK_TYPE::ART:
        std::cout.width(0);
        std::cout << "Type: ";
        std::cout.width(10);
        std::cout << getBookType(book.type.art.bookType) << '|';
        break;
    case BOOK_TYPE::CHILD:
        std::cout.width(0);
        std::cout << "Type: ";
        std::cout.width(10);
        std::cout << getBookType(book.type.child.bookType) << '|';
        break;
    default:
        break;
    }

    std::cout << std::endl;

}

void library::outPut(Book *books, int count){
    std::cout << "### TABLE OF BOOKS!!! ###" << std::endl;
    for (int index = 0; index < count; index++){
        library::outPutBook(books[index], index);
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void library::outKeyToBook(Library lib){
    std::cout << "### TABLE OF BOOKS BY KEYS!!! ###" << std::endl;
    for (int index = 0; index < lib.bookCout; index++){
        int BookIndex = lib.keys[index].index;
        outPutBook(lib.books[BookIndex], index);
    }
}

void library::selectOperation(OPERATION oper, Library &lib, const char *LibFile){
    switch (oper) {
    case OPERATION::EXIT:
        std::exit(0);
        break;
    case OPERATION::ADD:
        library::addBook(lib, LibFile);
        break;
    case OPERATION::DELETE:
        break;
    case OPERATION::OUT_PUT:
        library::outPut(lib.books, lib.bookCout);
        library::outPut(lib.keys, lib.bookCout);
        library::outKeyToBook(lib);
        break;
    case OPERATION::SORT:
        break;
    case OPERATION::SEARCH:
        //library::search(lib);
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
