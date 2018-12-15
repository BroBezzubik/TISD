#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdlib>
#include <limits>

#define QUEUE_SIZE 5

extern int countType1, countType2;
extern double arriveTime1, arriveTime2, arriveTime3, arriveTime4;
extern double processTime1, processTime2, processTime3, processTime4;
extern double GLOBAL_PROCCES_TIME, GLOBAL_ARRIVE_TIME_TYPE1, GLOBAL_ARRIVE_TIME_TYPE2;

namespace queue {
    struct Queue;
    struct DynamicQueue;
    struct Node;
    struct Request;

    void intro();
    void infTimeRange();
    void changeTimeRange();
    void checkStream(std::basic_istream<char> &str);
    void simulation();
    void addElements(Queue &queue, Queue &queue2);
    Request generateElement(double arTime1, double arTime2,
                            double procTime1, double procTime2);
    Node* generateDynamElement(double arrTime1, double arrTime2,
                              double procTime1, double procTime2);
    void addElements(DynamicQueue &queue, DynamicQueue &queue2);
    void addElement(Queue &queue, Request req);
    void addElement(DynamicQueue &queue, Node &req);
    void process(Queue &queue1, Queue &queue2);
    void process(DynamicQueue &queue1, DynamicQueue &queue2);
}

struct queue::Request{
    Request();
    double tArrive;
    double tProcess;
};

struct queue::Queue{
    Queue();
    Request requests[QUEUE_SIZE];
    int count;
    Request *pIn;
    Request *pOut;
    Request *begin;
    Request *end;
};

struct queue::DynamicQueue{
    DynamicQueue();
    Node *pIn;
    Node *pOut;
    int count;
};

struct queue::Node{
    Node();
    Request item;
    Node *next;
};

#endif // QUEUE_H
