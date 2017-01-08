#ifndef SYMULATOR_INCLUDED
#define SYMULATOR_INCLUDED
#include <iostream>
#include <ctime>

#include "MyList.hpp"


/*
    Struktura implementująca symulator zdarzen.

    start - czas startu symulacji
    MyIndexList - tablica indeksująca
*/

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
