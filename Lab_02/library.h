#ifndef LIBRARY_H
#define LIBRARY_H

#define BUFFER_SIZE 40
#define LIBRARY_SIZE 100
#define STRING_BUFFER 200

namespace library {
    struct Library;
    struct Key;
    struct keyTable;
    struct TechBook;
    struct ArtBook;
    struct ChildBook;
    struct Book;

    enum BOOK_TYPE_KEY{ TECH = 0, ART, CHILD };
    enum TECH_TYPE{ RUSSAIN = 0, TRANSLATED };
    enum ART_TYPE{ ROMAN = 0, PLAY, POEM };
    enum CHILD_TYPE{FAIRY_TAILS = 0, CHILD_POEM};
    enum OPERATION_KEY{OUT_PUT = 0, ADD_BOOK, DELETE_BOOK, SORT_TABLE};

    union BookType;

    void loadBook(Library lib, char *bookData);
    void loadLib(Library lib, char *fileName);
    void updateKeyTable(Library &lib, keyTable &table);
    void loop(Library &lib, keyTable &table);
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
    long int count;
};
#endif // LIBRARY_H
