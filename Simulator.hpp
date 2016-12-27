#ifndef SYMULATOR_INCLUDED
#define SYMULATOR_INCLUDED
#include "MyList.hpp"
#include <iostream>
#include <ctime>

using namespace std;

struct Simulator{
    clock_t start;
    MyIndexList *eventList;

    Simulator(MyIndexList *l){
        eventList = l;
    }

    void normalSimulation();
    void secondSimulation(double t);
};


#endif // SYMULATOR_INCLUDED
