#include "Simulator.hpp"

void Simulator::normalSimulation()
{
    start = clock();
    float s;

    while(!eventList->empty())
    {
        if(clock() - start >= 1000*eventList->head->evt->next->time)
            eventList->deleteFirst();
    }

}

void Simulator::secondSimulation(double t)
{
    start = clock();
    float s;

    while((clock()-start)/1000000<t)
    {
        if(clock() - start >= 1000*eventList->head->evt->next->time)
        {
            cout<<"Time: "<<clock() - start << " " << 1000*eventList->head->evt->next->time<<endl;
            if(eventList->head->evt->next->num)
            {
                for(int i=0; i<=eventList->head->evt->num; i++)
                {
                    cout<<"Dodano nowe zdarzenie : "<<eventList->head->evt->next->time<<" "<<eventList->head->evt->next->time + eventList->head->evt->next->dt<<endl;
                    eventList->addEvent(new Event(eventList->head->evt->next->time + eventList->head->evt->next->dt,"zdarzenie wywołane"));
                }
            }
            eventList->deleteFirst();
        }
    }

}
