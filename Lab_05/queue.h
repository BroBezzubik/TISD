#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_MAX_SIZE 100

namespace queue {
    template <typename T>
    struct Queue;

    template <typename T>
    struct Dynamic_queue;

    template <typename T>
    struct Node;

    struct Request;
}

template <typename T>
struct queue::Queue{
    long int count = 0;
    T elements[QUEUE_MAX_SIZE];
    T *pin;
    T *pout;
    T *fElement;
    T *lastElement;
};

struct queue::Request{
    double incomeTime;
    double processTime;
};

template <typename T>
struct queue::Node{
    T element;
    Node *next;
};

template <typename T>
struct queue::Dynamic_queue{
    long int count;
    queue::Node<T> *pout;
    queue::Node<T> *pin;
};

#endif // QUEUE_H
