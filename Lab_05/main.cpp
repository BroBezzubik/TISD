#include "queue.h"
#include <iostream>

int main(){
    Queue::TimeRanges tmr;
    Queue::setUp(tmr);
    Queue::simulation(tmr);

    return 0;
}
