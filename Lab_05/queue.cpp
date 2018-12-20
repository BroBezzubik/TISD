#include "queue.h"
#include <cstdlib>
#include <iostream>

Queue::TimeRanges::TimeRanges(double t1, double t2, double t3, double t4,
                              double p1, double p2, double p3, double p4){
    arriveTime1 = t1;
    arriveTime2 = t2;
    arriveTime3 = t3;
    arriveTime4 = t4;

    processTime1 = p1;
    processTime2 = p2;
    processTime3 = p3;
    processTime4 = p4;
}

Queue::WorksTime::WorksTime(){
    arriveTime1 = 0;
    arriveTime2 = 0;
    processTime = 0;
    departureTime = 0;
}

Queue::Queue::Queue(){
   pIn = pOut = items;
   count = 0;
   arrivedItems = 0;
   departedItems = 0;
}

Queue::Request::Request(double arrTime, double procTime){
    arriveTime = arrTime;
    processTime = procTime;
}

Queue::Node::Node(){
    next = NULL;
}

Queue::DynamicQueue::DynamicQueue(){
    pOut = pIn = NULL;
    count = 0;
    arrivedItems = 0;
    departedItems = 0;
}

void Queue::timeRangesInfo(TimeRanges &tmR){
    std::cout << "### 1st type of request ###" << std::endl;
    std::cout << "Time to arrive: " << tmR.arriveTime1 << " - " << tmR.arriveTime2 << std::endl;
    std::cout << "Time to process: " << tmR.processTime1 << " - " << tmR.processTime2 << std::endl;
    std::cout << "### 2nd type of request ###" << std::endl;
    std::cout << "Time to arrive: " << tmR.arriveTime3 << " - " << tmR.arriveTime4 << std::endl;
    std::cout << "Time to process: " << tmR.processTime3 << " - " << tmR.processTime4 << std::endl;
}

void Queue::checkStream(std::basic_istream<char> &strm){
    if (!strm){
        throw "Invalid value";
    }
}


void Queue::setUp(TimeRanges &tmR){
    timeRangesInfo(tmR);
    std::cout << "Do you want to change ranges? (1 YES/ 0 NO)" << std::endl;
    int answer = 0;
    std::cout << ">> ";
    std::cin >> answer;
    if (answer){
        try{
            double
        } catch (const char *msg){

        }
    }
}


void Queue::simulation(TimeRanges &tmR){

}


