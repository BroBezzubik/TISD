#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <ctime>

#define STRING_BUFFER_UINPUT 50
#define STRING_BUFFER 30
#define LIBRARY_MAX_SIZE 1000

namespace library {
    enum BOOK_TYPE{TECH = 0, ART, CHILD};
    enum TECH_TYPE{RUSSIAN, TRANSLATED};
    enum ART_TYPE{NOVEL, PLAY, POEM};
    enum CHILD_TYPE{CHILD_POEM, FAIRY_TAILS};
    enum OPERATION{EXIT = 0, ADD, DELETE, OUT_PUT, SORT, SEARCH};

    struct TechBook;
    struct ChildBook;
    struct ArtBook;
    struct Book;
    struct Key;
    struct Library;
    union BookType;

    std::vector<std::string> split(const std::string &str);
    void loadBook(Book &book, const std::string &buffer);
    void loadKey(Book &book, Key &key, int index);
    void loadLib(Library &lib, const char *libFile);
    void addBook(Library &lib, const char *libFile);
    void uploadBook(Book *book, const char *libFile);
    void deleteBook(Library &lib, const char *libFile);
    void search(Library &lib);
    std::string getBookType(TECH_TYPE type);
    std::string getBookType(ART_TYPE type);
    std::string getBookType(CHILD_TYPE type);
    void outPutBook(Book &book, int index);
    void outKeyToBook(Library lib);
    void outPut(Book *books, int count);
    void outPut(Key *keys, int count);
    void loop(Library &lib, const char *libFile);
    OPERATION getOperation(void);
    void selectOperation(OPERATION oper, Library &lib, const char *LibFil);
    int cmpBooks(const void *tmp1, const void *tmp2);
    int cmpKeys(const void *tmp1, const void *tmp2);
    void sort(Library &lib, const char *fileName);
    void bubbleSort(Book *books, int count);
    void bubbleSort(Key *keys, int count);
}

struct library::TechBook{
    TECH_TYPE bookType;
    int year;
};

struct library::ChildBook{
    CHILD_TYPE bookType;
};

struct library::ArtBook{
    ART_TYPE bookType;
};

union library::BookType{
    TechBook tech;
    ChildBook child;
    ArtBook art;
};

struct library::Book{
    char bookName[STRING_BUFFER];
    char author[STRING_BUFFER];
    char publisher[STRING_BUFFER];
    int pageCount;
    BOOK_TYPE bookType;
    union BookType type;
};

struct library::Key{
    int index;
    int page;
};

struct library::Library{
    Book books[LIBRARY_MAX_SIZE];
    Key keys[LIBRARY_MAX_SIZE];
    int bookCout;
};

#endif // LIBRARY_H
