#ifndef LIBRARY_H
#define LIBRARY_H

#define BUFFER_SIZE 40
#define LIBRARY_SIZE 100
#define STRING_BUFFER 100

const char DEF_LIB = "LIB.CSV";

namespace library {
    struct Library;
    struct Key;
    struct keyTable;
    struct TechBook;
    struct ArtBook;
    struct ChildBook;
    struct Book;

    enum BOOK_TYPE_KEY{ TECH, ART, CHILD };
    enum TECH_TYPE{ RUSSAIN, TRANSLATED };
    enum ART_TYPE{ ROMAN, PLAY, POEM };
    enum CHILD_TYPE{FAIRY_TAILS, CHILD_POEM};

    union BookType;

    void loadLibrary(Library &lib, char *file = DEF_LIB);
    void saveLibrary(Library &lib, char *file = DEF_LIB);
}

struct library::Key{
    int libraryIndex;
    int pageCout;
};

struct library::keyTable{
    Key table[LIBRARY_SIZE];
};

struct library::TechBook
{
    TECH_TYPE type;
    int year;
};

struct library::ArtBook{
    ART_TYPE type;
};

struct library::ChildBook{
    CHILD_TYPE type;
};

union library::BookType{
    TechBook tech;
    ArtBook art;
    ChildBook child;
};

struct library::Book{
    char bookName[BUFFER_SIZE];
    char autor[BUFFER_SIZE];
    char publisher[BUFFER_SIZE];
    int pageCout;
    BOOK_TYPE_KEY bookTypeKey;
    BookType bookType;
};

struct library::Library{
    Book table[LIBRARY_SIZE];
    long int cout;
};
#endif // LIBRARY_H
