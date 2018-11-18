#ifndef STACK_H
#define STACK_H

#include <string>

#define STACK_MAX_SIZE 100

namespace stack{
    struct stack;
    struct dynamic_stack;
    struct stack_node;

    void add(stack st, string str);
    void add(dynamic_stack st, stack_node node);
    string pop(stack st);
    string pop(dynamic_stack st);

}

struct stack{
    stack() {}
    std::string elements[STACK_MAX_SIZE];
    int cout;
};

struct stack_node{
    stack_node();
    std::string element;
    stack_node *next;

};

struct dynamic_stack{
    int cout;
    stack_node *PS;
    dynamic_stack() {}
};
#endif // STACK_H
