#include "library.h"
#include <iostream>

using namespace std;

void library::loadLibrary(Library &lib, char *file){
    ifstream f;
    f.open(file, in);
    if (!f){
        throw  "File not found!!!";
    }

    char buffer[STRING_BUFFER];
    while(f.getline(buffer)){
        cout << buffer << endl;
    }
}
