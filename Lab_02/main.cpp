#include <iostream>
#include "library.h"

using namespace std;

int main(){
    char libFile[] = "LIB.CSV";
    library::Library lib;
    library::loadLib(lib, libFile);
//    library::loop(lib, libFile);
}


