#ifndef STACK_H
#define STACK_H

#include <string>

#define STACK_MAX_SIZE 10

namespace stack{
    enum STACK_OPERATIONS{EXIT = 0, ADD, POP, REV_OUT_STREAM, STATUS};

    struct stack;
    struct dynamic_stack;
    struct stack_node;

    void addElement(stack &st);
    void addElement(dynamic_stack &st);
    void add(stack &st, std::string &str);
    void add(dynamic_stack &st, stack_node &node);
    std::string pop(stack &st);
    std::string pop(dynamic_stack &st);
    void revOutStream(dynamic_stack &st);
    void revOutStream(stack &st);
    void status(stack &st);
    void status(dynamic_stack &st);
    void loop(dynamic_stack &st);
    void loop(stack &st);
    void userInfo();
    STACK_OPERATIONS getOper();
    void selectOper(STACK_OPERATIONS keyOper, stack &st);
    void selectOper(STACK_OPERATIONS keyOper, dynamic_stack &st);
}

struct stack::stack{
    stack();
    std::string elements[STACK_MAX_SIZE];
    int count;
};

struct stack::stack_node{
    stack_node();
    std::string element;
    stack_node *next;

};

struct stack::dynamic_stack{
    int count;
    stack_node *PS;
    dynamic_stack();
};
#endif // STACK_H
