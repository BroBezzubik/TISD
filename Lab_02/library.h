#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

#define STRING_BUFFER 30
#define LIBRARY_MAX_SIZE 100

namespace library {
    enum BOOK_TYPE{TECH = 0, ART, CHILD};
    enum TECH_TYPE{RUSSIAN, TRANSLATED};
    enum ART_TYPE{NOVEL, PLAY, POEM};
    enum CHILD_TYPE{CHILD_POEM, FAIRY_TAILS};

    struct TechBook;
    struct ChildBook;
    struct ArtBook;
    struct Book;
    struct Key;
    struct Library;
    union BookType;

    std::vector<std::string> split(const std::string &str);
    void loadBook(Book &book, const std::string &buffer);
    void loadKey(const Book &book, Key &key);
    void loadLib(Library &lib, const char *libFile);
    void loop(Library &lib, const char *libFile);
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
    Book *book;
    int page;
};

struct library::Library{
    Book books[LIBRARY_MAX_SIZE];
    Key keys[LIBRARY_MAX_SIZE];
    int bookCout;
};

#endif // LIBRARY_H
