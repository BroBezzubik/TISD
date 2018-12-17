#include <cstdlib>
#include <iostream>
#include <limits>
#include "queue.h"
#include <random>
#include <chrono>

queue::time::time(){
    sumLengQueue1 = 0;
    sumLengQueue2 = 0;
    ARRIVE_TIME_TYPE1 = 0;
    ARRIVE_TIME_TYPE2 = 0;
    PROCESS_TIME = 0;
    DEPARTURE_TIME = 0;
    GLOBAL_TIME = 0;
}

queue::Request::Request(){
    tArrive = 0;
    tProcess = 0;
}

queue::Queue::Queue(){
    count = 0;
    loggedItems = 0;
    releasedItems = 0;
    pIn = &requests[0];
    pOut = &requests[0];
    begin = &requests[0];
    end = &requests[QUEUE_SIZE - 1];
}

queue::DynamicQueue::DynamicQueue(){
    pIn = NULL;
    pOut = NULL;
    count = 0;
}

queue::Node::Node(){
    next = NULL;
}

void queue::intro(){
    std::cout << "Welcome to the programm with 2 types queues!!!" << std::endl;
    std::cout << std::endl;
}

void queue::infTimeRange(){
    std::cout << "### Time range inf: ###" << std::endl << std::endl;
    std::cout << "1st type of request:" << std::endl;
    std::cout << "### Min time to arrive: " << arriveTime1 << std::endl;
    std::cout << "### Max time to arrive: " << arriveTime2 << std::endl;
    std::cout << "### Min time to process: " << processTime1 << std::endl;
    std::cout << "### Max time to process: " << processTime2 << std::endl;

    std::cout << std::endl;

    std::cout << "2nd type of request:" << std::endl;
    std::cout << "### Min time to arrive: " << arriveTime3 << std::endl;
    std::cout << "### Max time to arrive: " << arriveTime4 << std::endl;
    std::cout << "### Min time to process: " << processTime3 << std::endl;
    std::cout << "### Max time to process: " << processTime4 << std::endl;
}

void queue::checkStream(std::basic_istream<char> &str){
    if (!str){
        str.clear();
        str.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw "Wrong value!";
    }
}

void queue::changeTimeRange(){
    int answer = 0;
    std::cout << "Do you wand change time range?" << std::endl;
    std::cout << "0) No!" << std::endl;
    std::cout << "1) Yes!" << std::endl;
    std::cout << ">> ";
    std::cin >> answer;
    queue::checkStream(std::cin);
    if (answer == 1){
        double arriveTmp1, arriveTmp2, arriveTmp3, arriveTmp4;
        double processTmp1, processTmp2, processTmp3, processTmp4;

        try{
            std::cout << "### 1st type of request ###" << std::endl;
            std::cout << "Min time to arrive: ";
            std::cin >> arriveTmp1;
            queue::checkStream(std::cin);

            std::cout << "Max time to arrive: ";
            std::cin >> arriveTmp2;
            queue::checkStream(std::cin);

            std::cout << "Min time to process: ";
            std::cin >> processTmp1;
            queue::checkStream(std::cin);

            std::cout << "Max time to process: ";
            std::cin >> processTmp2;
            queue::checkStream(std::cin);

            std::cout << std::endl << "### 2nd type of request ###" << std::endl;
            std::cout << "Min time to arrive: ";
            std::cin >> arriveTmp3;
            queue::checkStream(std::cin);

            std::cout << "Max time to arrive: ";
            std::cin >> arriveTmp4;
            queue::checkStream(std::cin);

            std::cout << "Min time to process: ";
            std::cin >> processTmp3;
            queue::checkStream(std::cin);

            std::cout << "Max time to process: ";
            std::cin >> processTmp4;
            queue::checkStream(std::cin);
        } catch (const char *msg){
            throw msg;
        }
        arriveTime1 = arriveTmp1;
        arriveTime2 = arriveTmp2;
        arriveTime3 = arriveTmp3;
        arriveTime4 = arriveTmp4;

        processTime1 = processTmp1;
        processTime2 = processTmp2;
        processTime3 = processTmp3;
        processTime4 = processTmp4;

        std::cout << "Change seccessful!" << std::endl;
    }
}

queue::Request queue::generateElement(double arTime1, double arTime2, double procTime1, double procTime2){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(arTime1, arTime2);
    std::uniform_real_distribution<double> distribution2(procTime1, procTime2);

    double arriveTime = distribution(generator);
    double processTime = distribution2(generator);

    Request req;
    req.tArrive = arriveTime;
    req.tProcess = processTime;

    return req;
}

queue::Node* queue::generateDynamElement(double arrTime1, double arrTime2, double procTime1, double procTime2){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> uniform1(arrTime1, arrTime2);
    std::uniform_real_distribution<double> uniform2(procTime1, procTime2);

    double arriveTime = uniform1(generator);
    double proccesTime= uniform2(generator);

    Node *tmp = new Node;
    tmp->item.tArrive = arriveTime;
    tmp->item.tProcess = proccesTime;

    return tmp;
}

int queue::addElement(Queue &queue, Request req){
    if (queue.count >= QUEUE_SIZE){
        return 0;
    } else {
        *queue.pIn = req;
        queue.count++;
        queue.loggedItems++;
        queue.pIn++;
        if (queue.pIn > queue.end){
            queue.pIn = queue.begin;
        }
        return 1;
    }
}

void queue::addElements(Queue &queue, Queue &queue2){
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::default_random_engine engine (seed);
//    std::uniform_int_distribution<int> distribution(1, 5);
//    int elementsCount = distribution(engine);
    for (int i = 0; i < 1; i++){
        int type = rand() % 100;
        Request req;
        if (type % 2 == 0){
            req = generateElement(arriveTime1, arriveTime2,
                                  processTime1, processTime2);
            addElement(queue, req);
        } else {
            req = generateElement(arriveTime3, arriveTime4,
                                  processTime3, processTime4);
            addElement(queue2, req);
        }
    }
}

int queue::addElement(DynamicQueue &queue, Node &req){
    if (queue.count >= QUEUE_SIZE){
        return 0;
    } else {
        queue.pIn->next = &req;
        queue.pIn = &req;
        queue.count++;
    }
    return 1;
}

void queue::addElements(DynamicQueue &queue, DynamicQueue &queue2){
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine engine (seed);
    //std::uniform_int_distribution<int> distribution(1, 5);
    //int elementsCount = distribution(engine);
    for (int i = 0; i < 1; i++){
        int type = rand() % 2;
        Node *req;
        if (type == 0){
            req = generateDynamElement(arriveTime1, arriveTime2,
                                  processTime1, processTime2);
            if(addElement(queue, *req)){
                queue.loggedItems++;
            }
        } else if (type == 1){
            req = generateDynamElement(arriveTime3, arriveTime4,
                                  processTime3, processTime4);
            if(addElement(queue2, *req)){
                queue.loggedItems++;
            }
        }
    }
}

void queue::updateQueueDisk(Queue &que){
    que.count--;
    que.releasedItems++;
    que.pOut++;
    if (que.pOut > que.end){
        que.pOut = que.begin;
    }
}

void queue::process(Queue &queue1, Queue &queue2, time &tm){
    if (queue1.count != 0 && queue2.count != 0){
        double arrTime1 = tm.ARRIVE_TIME_TYPE1 + queue1.pOut->tArrive;
        double arrTime2 = tm.ARRIVE_TIME_TYPE2 + queue2.pOut->tArrive;

        if (tm.DEPARTURE_TIME >= arrTime1){
            tm.DEPARTURE_TIME += queue1.pOut->tProcess;
            tm.ARRIVE_TIME_TYPE1 += queue1.pOut->tArrive;
            tm.PROCESS_TIME += queue1.pOut->tProcess;
            tm.sumLengQueue1 += queue1.count;
            queue::updateQueueDisk(queue1);

        } else if (tm.DEPARTURE_TIME >= arrTime2){
            tm.DEPARTURE_TIME += queue2.pOut->tProcess;
            tm.ARRIVE_TIME_TYPE2 += queue2.pOut->tArrive;
            tm.PROCESS_TIME += queue2.pOut->tProcess;
            tm.sumLengQueue2 += queue2.count;
            queue::updateQueueDisk(queue2);

        } else if (arrTime1 < arrTime2){
            tm.DEPARTURE_TIME = arrTime1;

        } else {
            tm.DEPARTURE_TIME = arrTime2;
        }

    } else if (queue1.count != 0 && queue2.count == 0){
        double arrTime = tm.ARRIVE_TIME_TYPE1 + queue1.pOut->tArrive;

        if (tm.DEPARTURE_TIME >= arrTime){
            tm.DEPARTURE_TIME = arrTime + queue1.pOut->tProcess;
            tm.ARRIVE_TIME_TYPE1 += queue1.pOut->tArrive;
            tm.PROCESS_TIME += queue1.pOut->tProcess;
            tm.sumLengQueue1 += queue1.count;
            queue::updateQueueDisk(queue1);

        } else if (tm.DEPARTURE_TIME < arrTime){
            tm.DEPARTURE_TIME = arrTime;
        }

    } else if (queue1.count == 0 && queue2.count != 0){
        double arrTime = tm.ARRIVE_TIME_TYPE2 + queue2.pOut->tArrive;

        if (tm.DEPARTURE_TIME >= arrTime){
            tm.DEPARTURE_TIME = arrTime + queue1.pOut->tProcess;
            tm.ARRIVE_TIME_TYPE2 += queue2.pOut->tArrive;
            tm.PROCESS_TIME += queue2.pOut->tArrive;
            tm.sumLengQueue2 += queue2.count;
            queue::updateQueueDisk(queue2);

        } else if (tm.DEPARTURE_TIME < arrTime){
            tm.DEPARTURE_TIME = arrTime;
        }
    }
}

void queue::updateQueueDisk(DynamicQueue &que){
    que.count--;
    que.releasedItems++;
    Node *tmp = que.pOut;
    que.pOut = que.pOut->next;
    delete tmp;
}

void queue::process(DynamicQueue &queue1, DynamicQueue &queue2, time &tm){
    if (queue1.count != 0 && queue2.count != 0){
        double arrTime1 = tm.ARRIVE_TIME_TYPE1 + queue1.pOut->item.tArrive;
        double arrTime2 = tm.ARRIVE_TIME_TYPE2 + queue2.pOut->item.tArrive;

        if (tm.DEPARTURE_TIME >= arrTime1){
            tm.DEPARTURE_TIME += queue1.pOut->item.tArrive;
            tm.ARRIVE_TIME_TYPE1 += queue1.pOut->item.tArrive;
            tm.sumLengQueue1 += queue1.count;
            queue::updateQueueDisk(queue1);

        } else if (tm.DEPARTURE_TIME >= arrTime2){
            tm.DEPARTURE_TIME += queue2.pOut->item.tArrive;
            tm.ARRIVE_TIME_TYPE2 += queue2.pOut->item.tArrive;
            tm.sumLengQueue2 += queue2.count;
            queue::updateQueueDisk(queue2);

        } else if (arrTime1 < arrTime2){
            tm.DEPARTURE_TIME = arrTime1;

        } else {
            tm.DEPARTURE_TIME = arrTime2;
        }
    } else if (queue1.count != 0 && queue2.count == 0){
        double arrTime = tm.ARRIVE_TIME_TYPE1 + queue1.pOut->item.tArrive;

        if (tm.DEPARTURE_TIME > arrTime){
            tm.DEPARTURE_TIME += queue1.pOut->item.tArrive;
            tm.ARRIVE_TIME_TYPE1 += queue1.pOut->item.tArrive;
            tm.sumLengQueue1 += queue1.count;
            queue::updateQueueDisk(queue1);

        } else {
            tm.DEPARTURE_TIME = arrTime;
        }

    } else if (queue1.count == 0 && queue2.count != 0){
        double arrTime = tm.ARRIVE_TIME_TYPE2 + queue2.pOut->item.tArrive;

        if (tm.DEPARTURE_TIME > arrTime){
            tm.DEPARTURE_TIME += queue2.pOut->item.tArrive;
            tm.ARRIVE_TIME_TYPE2 += queue2.pOut->item.tArrive;
            tm.sumLengQueue2 += queue2.count;
            queue::updateQueueDisk(queue2);
        } else {
            tm.DEPARTURE_TIME = arrTime;
        }
    }
}

void queue::simulationInfo(Queue &queue1, Queue &queue2, time &tm){
    std::cout << "### Simulation info ###" << std::endl;
    std::cout << std::endl;
    std::cout << "Current lengh of type1: " << queue1.count << std::endl;
    std::cout << "Current lengh of type2: " << queue2.count << std::endl;
    std::cout << "Middle time to arrive type1: " << tm.ARRIVE_TIME_TYPE1 / queue1.releasedItems << std::endl;
    std::cout << "Middle time to arrive type2: " << tm.ARRIVE_TIME_TYPE2 / queue2.releasedItems << std::endl;
    std::cout << "Middle count element in queue type1: " << (double) (tm.sumLengQueue1 / queue1.releasedItems) << std::endl;
    std::cout << "Middle count element in queue type2: " << (double) (tm.sumLengQueue2 / queue2.releasedItems) << std::endl;
    std::cout << "Count of Login 1st type elements: " << queue1.loggedItems << std::endl;
    std::cout << "Count of login 2nd type elements: " << queue2.loggedItems << std::endl;
    std::cout << "Count of departed elements 1st type: " << queue1.releasedItems << std::endl;
    std::cout << "Count of departed elements 2nd type: " << queue2.releasedItems << std::endl;
    std::cout << std::endl;
}

void queue::simulationResult(Queue &queue1, Queue &queue2, time &tm){
    std::cout << " ### !!!SIMULATION INFO!!! ### " << std::endl;
    std::cout << "@@@ 1st type of request @@@" << std::endl;
    std::cout << "Count of 1st type log in: " << queue1.loggedItems << std::endl;
    std::cout << "Count of 1st type relesed: " << queue1.releasedItems << std::endl;
    std::cout << std::endl;
    std::cout << "@@@ 2nd type of reques @@@" << std::endl;
    std::cout << "Count of 2nd type log in: " << queue2.loggedItems << std::endl;
    std::cout << "Count of 2nd type relesed: " << queue2.releasedItems << std::endl;

    double workTime;
    if (tm.ARRIVE_TIME_TYPE1 / queue1.releasedItems + tm.ARRIVE_TIME_TYPE2 / queue2.releasedItems > (processTime1 + processTime2) / 2 + (processTime3 + processTime4) / 2 ){
        workTime = tm.DEPARTURE_TIME;
    } else {
        workTime = tm.PROCESS_TIME;
    }

    std::cout << std::endl;
    std::cout << "Time of work is: " << workTime << std::endl;

    std::cout << "Expected time of work with 1st type: " <<

}

void queue::simulation(){
    queue::Queue queue1;
    queue::Queue queue2;
    time tm;
    int roof = 100;
    for(int index = 0;;index++){
        process(queue1, queue2, tm);
        addElements(queue1, queue2);

        if (queue1.releasedItems == roof){
            simulationInfo(queue1, queue2, tm);
            roof += 100;
        }

        if (queue1.releasedItems >= 1000){
            break;
        }
    }
    std::cout << tm.PROCESS_TIME << std::endl;
    std::cout << tm.DEPARTURE_TIME << std::endl;
    queue::simulationResult(queue1, queue2, tm);

    time tm1;
    DynamicQueue queue3;
    DynamicQueue queue4;
    roof = 100;
    for(int index = 0; ; index++){
        addElements(queue3, queue4);
        process(queue3, queue4, tm1);

        if (index == roof){
            //simulationInfo(queue3, queue4);
            roof += 100;
        }
        if (queue3.releasedItems >= 1000){
            break;
        }
    }
}
