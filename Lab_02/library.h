#ifndef LIBRARY_H
#define LIBRARY_H

#define TABLE_SIZE 1000
#define BUFFER_SIZE 50

namespace library{
    struct Library;
    struct Book;
    struct TechBook;
    struct ArtBook;
    struct ChildBook;
    union BookType;
    enum bookTypeKey;
    enum TechBookType;
    enum ArtBookType;
    enum ChildBookType;
}

struct library::Library{
    char fileName[BUFFER_SIZE];
    Book table[TABLE_SIZE];
    int bookCout;
}

struct library::Book{
    char autorName[BUFFER_SIZE];
    char bookName[BUFFER_SIZE];
    char publisher[BUFFER_SIZE];
    int pageCout;
    BookType type;
}

#endif // LIBRARY_H
