#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdlib>
#include <limits>

#define QUEUE_SIZE 100

extern double arriveTime1, arriveTime2, arriveTime3, arriveTime4;
extern double processTime1, processTime2, processTime3, processTime4;

namespace queue {
    struct Queue;
    struct DynamicQueue;
    struct Node;
    struct Request;
    struct time;

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
    int addElement(Queue &queue, Request req);
    int addElement(DynamicQueue &queue, Node &req);
    void process(Queue &queue1, Queue &queue2, time &tm);
    void updateQueueDisk(Queue &que);
    void updateQueueDisk(DynamicQueue &que);
    void process(DynamicQueue &queue1, DynamicQueue &queue2, time &tm);
    void simulationInfo(Queue &queue1, Queue &queue2, time &tm);
    void simulationInfo(DynamicQueue &queue1, DynamicQueue &queue2);
    void simulationResult(Queue &queue1, Queue &queue2, time &tm);
    void simulationREsult(DynamicQueue &queue1, DynamicQueue &queue2);
}

struct queue::time{
    time();
    int sumLengQueue1;
    int sumLengQueue2;
    double ARRIVE_TIME_TYPE1;
    double ARRIVE_TIME_TYPE2;
    double DEPARTURE_TIME;
    double PROCESS_TIME;
    double GLOBAL_TIME;
};

struct queue::Request{
    Request();
    double tArrive;
    double tProcess;
};

struct queue::Queue{
    Queue();
    Request requests[QUEUE_SIZE];
    int loggedItems;
    int releasedItems;
    int count;
    Request *pIn;
    Request *pOut;
    Request *begin;
    Request *end;
};

struct queue::DynamicQueue{
    DynamicQueue();
    int loggedItems;
    int releasedItems;
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
