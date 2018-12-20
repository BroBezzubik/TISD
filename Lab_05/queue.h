#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdlib>

#define QUEUE_MAX_SIZE 1000
#define PROCESS_LIMIT 1000

#define AR_TIME1 1
#define AR_TIME2 5
#define AR_TIME3 0
#define AR_TIME4 3

#define PROC_TIME1 0
#define PROC_TIME2 4
#define PROC_TIME3 0
#define PROC_TIME4 1


namespace Queue{
    struct Queue;
    struct DynamicQueue;
    struct Request;
    struct Node;
    struct TimeRanges;
    struct WorksTime;

    void setUp(TimeRanges &tmR);
    void timeRangesInfo(TimeRanges &tmR);
    void checkStream(std::basic_istream<char> &strm);
    void simulation(TimeRanges &tmR);
}

struct Queue::TimeRanges{
    TimeRanges(double t1 = AR_TIME1, double t2 = AR_TIME2, double t3 = AR_TIME3, double t4 = AR_TIME4,
               double p1 = PROC_TIME1, double p2 = PROC_TIME2, double p3 = PROC_TIME3, double p4 = PROC_TIME4);

    double arriveTime1, arriveTime2, arriveTime3, arriveTime4;
    double processTime1, processTime2, processTime3, processTime4;
};

struct Queue::WorksTime{
    WorksTime();
    double arriveTime1;
    double arriveTime2;
    double processTime;
    double departureTime;
};

struct Queue::Request{
    Request(double arrTime = 0, double procTime = 0);
    double arriveTime;
    double processTime;
};

struct Queue::Queue{
    Queue();
    Request items[QUEUE_MAX_SIZE];
    Request *pIn;
    Request *pOut;
    int count;
    int arrivedItems;
    int departedItems;
};

struct Queue::Node{
    Node();
    Request items;
    Node *next;
};

struct Queue::DynamicQueue{
    DynamicQueue();
    Node *pOut;
    Node *pIn;
    int count;
    int arrivedItems;
    int departedItems;
};

#endif // QUEUE_H
