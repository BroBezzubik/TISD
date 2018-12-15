#include "queue.h"
#include <iostream>
#include <cstdlib>

double arriveTime1 = 1;
double arriveTime2 = 5;
double arriveTime3 = 0;
double arriveTime4 = 3;

double processTime1 = 0;
double processTime2 = 4;
double processTime3 = 0;
double processTime4 = 1;

int main(){
    queue::intro();
    queue::infTimeRange();
    try{
        queue::changeTimeRange();
    } catch (const char *msg){
        std::cerr << msg << std::endl;
    }
    queue::simulation();
}
