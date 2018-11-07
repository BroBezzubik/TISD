#include <iostream>
#include "library.h"

using namespace std;

int main(){
    char fileName[] = "LIB.CSV";
    library::Library lib;
    library::loadLib(lib, fileName);
    library::keyTable keys;
    library::updateKeyTable(lib, keys);
    library::loop(lib, keys);
}

