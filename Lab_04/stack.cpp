#include "stack.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <ctime>


void stack::loop(dynamic_stack &st){
    for(;;){
        try{
            userInfo();
            STACK_OPERATIONS oper = getOper();
            if (oper == STACK_OPERATIONS::EXIT){
                break;
            }
            selectOper(oper, st);
        } catch(const char *msg){
            std::cerr << msg << std::endl;
        }
    }
}

void stack::loop(stack &st){
    for(;;){
        try{
            userInfo();
            STACK_OPERATIONS oper = getOper();
            if (oper == STACK_OPERATIONS::EXIT){
                break;
            }
            selectOper(oper, st);
        } catch(const char *msg){
        std::cerr << msg << std::endl;
        }
    }
}

stack::stack::stack(){
    count = 0;
}

stack::dynamic_stack::dynamic_stack(){
    count = 0;
    PS = NULL;
}

stack::stack_node::stack_node(){
    next = NULL;
}

void stack::userInfo(){
    std::cout << "0) EXIT" << std::endl;
    std::cout << "1) ADD" << std::endl;
    std::cout << "2) POP" << std::endl;
    std::cout << "3) Revers words" << std::endl;
    std::cout << "4) Status" << std::endl;
}

stack::STACK_OPERATIONS stack::getOper(){
    std::cout << "Select operation: ";
    int key;
    std::cin >> key;
    if (key != STACK_OPERATIONS::EXIT && key != STACK_OPERATIONS::ADD &&
            key != STACK_OPERATIONS::POP && key != REV_OUT_STREAM && key != STACK_OPERATIONS::STATUS ||
            std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw "Invalid operation key!";
    }
    return (STACK_OPERATIONS) key;
}

void stack::selectOper(STACK_OPERATIONS keyOper, stack &st){
    switch (keyOper) {
    case STACK_OPERATIONS::EXIT:
        break;

    case STACK_OPERATIONS::ADD:
        std::cout << std::endl;
        std::cout << "### Selected Add element! ###" << std::endl;
        addElement(st);
        std::cout << std::endl;
        break;

    case STACK_OPERATIONS::POP:
        std::cout << std::endl;
        std::cout << "### Selected 'Pop'! ###" << std::endl;
        pop(st);
        std::cout << std::endl;
        break;

    case STACK_OPERATIONS::REV_OUT_STREAM:
        std::cout << std::endl;
        std::cout << "### Selected Out Stream! ###";
        std::cout << std::endl;
        std::clock_t start;
        double duration;
        start = std::clock();
        revOutStream(st);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Duration is: " << duration << std::endl;
        std::cout << std::endl;
        break;

    case STACK_OPERATIONS::STATUS:
        std::cout << std::endl;
        std::cout << "### Selected 'Status'! ###" << std::endl;
        status(st);
        std::cout << std::endl;
        break;

    default:
        break;
    }
}

void stack::selectOper(STACK_OPERATIONS keyOper, dynamic_stack &st){
    switch (keyOper) {
    case STACK_OPERATIONS::EXIT:
        break;

    case STACK_OPERATIONS::ADD:
        std::cout << std::endl;
        std::cout << "### Selected Add element! ###" << std::endl;
        addElement(st);
        std::cout << std::endl;
        break;

    case STACK_OPERATIONS::POP:
        std::cout << std::endl;
        std::cout << "### Selected 'Pop'! ###" << std::endl;
        pop(st);
        std::cout << std::endl;
        break;

    case STACK_OPERATIONS::REV_OUT_STREAM:
        std::cout << std::endl;
        std::cout << "### Selected Out Stream! ###";
        std::cout << std::endl;
        std::clock_t start;
        double duration;
        start = std::clock();;
        revOutStream(st);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Duration: " << duration << std::endl;
        std::cout << std::endl;
        break;

    case STACK_OPERATIONS::STATUS:
        std::cout << std::endl;
        std::cout << "### Selected 'Status'! ###" << std::endl;
        status(st);
        std::cout << std::endl;
        break;

    default:
        break;
    }
}

void stack::addElement(dynamic_stack &st){
    std::cin.ignore();
    try{
        std::string str;
        std::cout << "Input word / words: ";
        std::getline(std::cin, str, '\n');
        std::istringstream inBuf(str);
        std::string tmp;
        while(std::getline(inBuf, tmp, ' ')){
            if (st.count < STACK_MAX_SIZE){
                stack_node *node = new stack_node;
                node->next = st.PS;
                st.PS = node;
                node->element = tmp;
                st.count++;
            } else {
                std::cout << "Stack is full. Delete some elements before add!";
                break;
            }
        }
    } catch (std::bad_alloc xa){
        std::cerr << "Can't allocate node!";
    }
}

void stack::addElement(stack &st){
    std::cin.ignore();
    try{
        std::string str;
        std::cout << "Input word / words: ";
        std::getline(std::cin, str, '\n');
        std::istringstream inBuf(str);
        std::string tmp;
        while(std::getline(inBuf, tmp, ' ')){
            if (st.count < STACK_MAX_SIZE){
                st.elements[st.count] = tmp;
                st.count++;
            } else {
                std::cout << "Stack is full. Delete some elements before add!";
                break;
            }
        }
    } catch (const char *msg){
        std::cerr << msg << std::endl;
    }
}

void stack::status(stack &st){
    if (st.count <= 0){
        std::cout << "(null)" << std::endl;
    } else {
        for (int index = st.count - 1; index >= 0; index--){
            std::cout << "|Index: ";
            std::cout.width(5);
            std::cout << index;
            std::cout.width(0);
            std::cout << "|Data: ";
            std::cout.width(20);
            std::cout << st.elements[index];
            std::cout.width(0);
            std::cout << "|Pointer: ";
            std::cout << &st.elements[index] << std::endl;
        }
    }
}

void stack::status(dynamic_stack &st){
    if (st.count <= 0){
        std::cout << "(null)" << std::endl;
    } else {
        int index = st.count - 1;
        for (stack_node *runer = st.PS; runer != NULL; runer = runer->next){
            std::cout << "|Index: ";
            std::cout.width(5);
            std::cout << index--;
            std::cout.width(0);
            std::cout << "|Data: ";
            std::cout.width(20);
            std::cout << runer->element;
            std::cout.width(0);
            std::cout << "|Pointer: ";
            std::cout << runer << std::endl;
        }
    }
}

std::string stack::pop(stack &st){
    std::string str;
    if (st.count == 0){
    } else {
        int count = st.count - 1;
        str = st.elements[count];
        st.elements[count].clear();
        st.count--;
    }
    return str;
}

std::string stack::pop(dynamic_stack &st){
    std::string str;
    if (st.PS == NULL){
       std::cout << "fix" << std::endl;
    } else {
        stack_node *node = st.PS;
        st.PS = node->next;
        str = node->element;
        st.count--;
        delete node;
    }
    return str;
}

void stack::revOutStream(stack &st){
    if (st.count == 0){
        std::cout << "(null)" << std::endl;
    } else {
        for (int index = st.count; index >= 0; index--){
            std::cout << pop(st) << " ";
        }
        std::cout << std::endl;
    }
}

void stack::revOutStream(dynamic_stack &st){
    if (st.PS == NULL){
        std::cout << "(null)" << std::endl;
    } else {
        for (;st.PS != NULL;){
            std::cout << pop(st) << " ";
        }
        std::cout << std::endl;
    }
}
