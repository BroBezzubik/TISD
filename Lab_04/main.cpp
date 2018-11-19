#include <iostream>
#include "stack.h"

int main()
{
    std::cout << "Welcome to the programm with 2 diff stacks!" << std::endl;
    std::cout << "1) Stack based on arrray" << std::endl;
    std::cout << "2) Stack based on list" << std::endl;

    std::cout << std::endl;
    std::cout << "#####" << std::endl;
    std::cout << "Now we work with first type of stack!" << std::endl;
    std::cout << "#####" << std::endl;
    std::cout << std::endl;

    stack::stack st;
    stack::loop(st);

    std::cout << std::endl;
    std::cout << "#####" << std::endl;
    std::cout << "Now we work with 2nd style of stack!" << std::endl;
    std::cout << "#####" << std::endl;
    std::cout << std::endl;
    stack::dynamic_stack *dmSt = new stack::dynamic_stack;
    stack::loop(*dmSt);
}
