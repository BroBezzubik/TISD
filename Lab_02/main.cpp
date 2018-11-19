#include <iostream>
#include "library.h"
#include <cstring>

using namespace std;

int main(){
    try{
        char libFile[] = "LIB.CSV";
        library::Library lib;
        library::loadLib(lib, libFile);
        std::cout << "Ima here!!";
        library::loop(lib, libFile);
    } catch (const char *msg){
        std::cerr << msg << std::endl;
    }
}

