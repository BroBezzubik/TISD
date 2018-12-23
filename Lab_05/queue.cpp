#include "queue.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <chrono>

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

Queue::SimulParameters::SimulParameters(){
    arriveTime1 = 0;
    arriveTime2 = 0;
    processTime = 0;
    departureTime = 0;
    sumElementsQueue1 = 0;
    sumElementsQueue2 = 0;
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
        strm.clear();
        strm.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw "Invalid value";
    }
}


void Queue::setUp(TimeRanges &tmR){
    timeRangesInfo(tmR);
    std::cout << "Do you want to change ranges? (1 YES/ 0 NO)" << std::endl;
    int answer = 0;
    std::cout << ">> ";
    std::cin >> answer;
    if (answer == 1){
        try{
            std::cout << "### 1st type of request ###" << std::endl;
            std::cout << "Input min and max arrive time: ";
            double arrTime1, arrTime2;
            std::cin >> arrTime1;
            std::cin >> arrTime2;
            checkStream(std::cin);

            std::cout << "Input min and max process time: ";
            double procTime1, procTime2;
            std::cin >> procTime1;
            std::cin >> procTime2;
            checkStream(std::cin);

            std::cout << "### 2nd type of request ###" << std::endl;
            std::cout << "Input min and max time arrive time: ";
            double arrTime3, arrTime4;
            std::cin >> arrTime3;
            std::cin >> arrTime4;
            checkStream(std::cin);

            std::cout << "Input min and max process time: ";
            double procTime3, procTime4;
            std::cin >> procTime3;
            std::cin >> procTime4;
            checkStream(std::cin);

            tmR.arriveTime1 = arrTime1;     tmR.arriveTime2 = arrTime2;
            tmR.processTime1 = procTime1;   tmR.processTime2 = procTime2;

            tmR.arriveTime3 = arrTime3;     tmR.arriveTime4 = arrTime4;
            tmR.processTime3 = procTime3;   tmR.processTime4 = procTime4;

        } catch (const char *msg){
           std::cerr << "Invalid Value!" << std::endl;
           std::cerr << "Failed chagne Time Ranges!" << std::endl;
        }
    }
}

Queue::Request Queue::generateRequest(double arrTime1, double arrTime2, double procTime1, double procTime2){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> arrT(arrTime1, arrTime2);
    std::uniform_real_distribution<> procT(procTime1, procTime2);
    Request req;
    req.arriveTime = arrT(gen);
    req.processTime = procT(gen);

    return req;
}

Queue::Node* Queue::generateNode(double arrTime1, double arrTime2, double procTime1, double procTime2){
    Request req = generateRequest(arrTime1, arrTime2, procTime1, procTime2);
    Node *node = new Node;
    node->items = req;

    return node;
}

void Queue::addReq(Queue &queue, Request &req){
    if (queue.count < QUEUE_MAX_SIZE){
        queue.pIn->arriveTime = req.arriveTime;
        queue.pIn->processTime = req.processTime;
        queue.count++;
        queue.arrivedItems++;
        queue.pIn++;
        if (queue.pIn >= &queue.items[QUEUE_MAX_SIZE]){
            queue.pIn = queue.items;
        }
    } else {
    }
}

void Queue::addReq(DynamicQueue &queue, Node &req){
    if (queue.count == 0){
        queue.pIn = &req;
        queue.pOut = &req;
    } else {
        queue.pIn->next = &req;
    }
    queue.pIn = &req;
    queue.arrivedItems++;
    queue.count++;
}

void Queue::extensionQueues(Queue &queue1, DynamicQueue &queue2, TimeRanges &tmr, SimulParameters &smp){
    int type = rand() / 100;
    Request req;
    if (type % 2 == 0){
        std::clock_t start = std::clock();
        req = generateRequest(tmr.arriveTime1, tmr.arriveTime2,
                              tmr.processTime1, tmr.processTime2);
        addReq(queue1, req);
        std::clock_t end = std::clock();
        smp.addTime1 =  (end - start);

    } else {
        std::clock_t start = std::clock();

        Node *node = generateNode(tmr.arriveTime3, tmr.arriveTime4,
                                  tmr.processTime3, tmr.processTime4);
        addReq(queue2, *node);
        std::clock_t end = std::clock();
        smp.addTime2 = (double) (end - start);
    }
}

void Queue::updateQueueParam(Queue &q){
    q.count--;
    q.departedItems++;
    q.pOut++;
    if (q.pOut >= &q.items[QUEUE_MAX_SIZE]){
        q.pOut = q.items;
    }
}

void Queue::updateQueueParam(DynamicQueue &q){
    Node *tmp = q.pOut;
    q.pOut = tmp->next;
    q.count--;
    q.departedItems++;

    delete tmp;
}

void Queue::processingReq(Queue &queue1, DynamicQueue &queue2, SimulParameters &smp){
    double arriveTime1 = 0;
    double arriveTime2 = 0;
    if (queue1.count != 0 && queue2.count != 0){
        arriveTime1 = smp.arriveTime1 + queue1.pOut->arriveTime;
        arriveTime2 = smp.arriveTime2 + queue2.pOut->items.arriveTime;
        if (smp.departureTime >= arriveTime1){
            std::clock_t start = std::clock();
            smp.departureTime += queue1.pOut->processTime;
            smp.arriveTime1 += queue1.pOut->arriveTime;
            smp.sumElementsQueue1 += queue1.count;
            smp.processTime += queue1.pOut->processTime;
            updateQueueParam(queue1);
            std::clock_t end = std::clock();
            smp.procTime1 = end - start;

        } else if (smp.departureTime >= arriveTime2){
            std::clock_t start = clock();
            smp.departureTime += queue2.pOut->items.processTime;
            smp.arriveTime2 += queue2.pOut->items.arriveTime;
            smp.sumElementsQueue2 += queue2.count;
            smp.processTime += queue2.pOut->items.processTime;
            updateQueueParam(queue2);
            std::clock_t end = clock();
            smp.procTime2 = end - start;

        } else {
            if (arriveTime1 <= arriveTime2){
                smp.departureTime = arriveTime1;

            } else {
                smp.departureTime = arriveTime2;
            }

        }
    } else if (queue1.count != 0 && queue2.count == 0){

        arriveTime1 = smp.arriveTime1 + queue1.pOut->arriveTime;
        if (smp.departureTime >= arriveTime1){
            std::clock_t start = clock();
            smp.departureTime += queue1.pOut->processTime;
            smp.arriveTime1 = queue1.pOut->arriveTime;
            smp.sumElementsQueue1 += queue1.count;
            smp.processTime += queue1.pOut->processTime;
            updateQueueParam(queue1);
            std::clock_t end = clock();
            smp.procTime1 = end - start;

        } else {
            smp.departureTime = arriveTime1;
        }

    } else if (queue1.count == 0 && queue2.count != 0){

        arriveTime2 = smp.arriveTime2 + queue2.pOut->items.arriveTime;
        if (smp.departureTime >= arriveTime2){
            std::clock_t start = clock();
            smp.departureTime += queue2.pOut->items.processTime;
            smp.arriveTime2 = queue2.pOut->items.arriveTime;
            smp.sumElementsQueue2 += queue2.count;
            smp.processTime += queue2.pOut->items.processTime;
            updateQueueParam(queue2);
            std::clock_t end = clock();
            smp.procTime2 = end - start;
        }
    }
}

void Queue::shomMemoryMap(SimulParameters &smp, int count){
    std::cout << "@@@ Memory map @@@" << std::endl;
    for (int index = 0; index <= count; index++){
        std::cout << &smp.memoryMap[index] << std::endl;
    }
}

void Queue::simulationResult(Queue q, DynamicQueue q2, SimulParameters smp){
    std::cout << std::endl;
    std::cout << "#########################" << std::endl;
    std::cout << "### SIMULATION RESULT ###" << std::endl;
    std::cout << "#########################" << std::endl;
    std::cout << std::endl;

    std::cout << "Time of work is: " << smp.departureTime << std::endl;
    std::cout << "Arrive 1st type: " << q.arrivedItems << std::endl;
    std::cout << "Arrive 2nd type: " << q2.arrivedItems << std::endl;
    std::cout << "Departed 1st type: " << q.departedItems << std::endl;
    std::cout << "Depatred 2nd type: " << q2.departedItems << std::endl;
    std::cout << std::endl;

    std::cout << "### Times ###" << std::endl;
    std::cout << "Time to add: " << smp.addTime1 << " ::: " << smp.addTime2 << std::endl;
    std::cout << "Time to process: " << smp.procTime1 << " ::: " << smp.procTime2 << std::endl;

    int answer = 0;
    std::cout << "Show map of memory? (1 Yes/ 0 No)" << std::endl;
    std::cout << ">>";
    std::cin >> answer;
    if (answer){
        shomMemoryMap(smp, q2.arrivedItems);
    }

}

void Queue::simulationInfo(Queue q, DynamicQueue q2,SimulParameters smp){
    std::cout << std::endl;
    std::cout << "#######################" << std::endl;
    std::cout << "### Simulation Info ###" << std::endl;
    std::cout << "#######################" << std::endl;
    std::cout << std::endl;
    std::cout << "@@@ 1st queue @@@" << std::endl;
    std::cout << std::endl;
    std::cout << "Lengh: " << q.count  << std::endl;
    std::cout << "Mid lengh: " << smp.sumElementsQueue1 / q.departedItems << std::endl;
    std::cout << "Mid time to arrive: " << smp.arriveTime1 / q.departedItems << std::endl;
    std::cout << std::endl;
    std::cout << "@@@ 2nd queue @@@" << std::endl;
    std::cout << std::endl;
    std::cout << "Lengh: " << q2.count << std::endl;
    std::cout << "Mid lengh: " << smp.sumElementsQueue2 / q2.departedItems << std::endl;
    std::cout << "Mid time to arrive: " << smp.arriveTime2 / q2.departedItems << std::endl;

}

void Queue::simulationQueue(TimeRanges &tmr){
    SimulParameters param;
    Queue queue1;
    DynamicQueue queue2;
    int infoLvl = 100;
    for (;;){
        extensionQueues(queue1, queue2, tmr, param);
        processingReq(queue1, queue2, param);

        if (queue1.departedItems == infoLvl){
            simulationInfo(queue1, queue2, param);
            infoLvl += 100;
        }

        if (queue1.departedItems == PROCESS_LIMIT){
            simulationResult(queue1, queue2, param);
            break;
        }
    }
}



void Queue::simulation(TimeRanges &tmR){
    std::cout << "### Simulation of programm with static queue ###" << std::endl << std::endl;
    simulationQueue(tmR);
}


