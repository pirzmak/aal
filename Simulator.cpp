#include "Simulator.hpp"
#include <fstream>

/*
    Symulacja podczas której wykonywane są wszystkie zdarzenia aż do ich wyczerpania
*/
void Simulator::normalSimulation()
{
    start = clock();
    fstream plik;
    plik.open( "logSimulation.txt", ios::out );
    while(!eventList->empty())
    {
        if(float((clock()-start))/CLOCKS_PER_SEC >= eventList->head->evt->next->time){
            cout<<"Usuniecie zdarzenia : "<<setprecision(4)<<eventList->head->evt->next->time<<" : "<<eventList->head->evt->next->kindOfEvent<<endl;
            plik<<"Usuniecie zdarzenia : "<<setprecision(4)<<eventList->head->evt->next->time<<" : "<<eventList->head->evt->next->kindOfEvent<<endl;

            eventList->deleteFirst();
        }

    }

}

/*
    Symulacja zdarzenia są wykonywane przez określony czas. Zdarzenia mogą powodować dodanie nowych zdarzeń.
*/
void Simulator::secondSimulation(double t)
{
    start = clock();
    srand( time( NULL ) );

    fstream plik;
    plik.open( "logSimulation.txt", ios::out );

    while(float((clock()-start))/CLOCKS_PER_SEC<t)
    {
        if(float((clock()-start))/CLOCKS_PER_SEC >= eventList->head->evt->next->time)
        {
            if(eventList->head->evt->next->num)
            {
                for(int i=0; i<=eventList->head->evt->num; i++)
                {
                    cout<<"Czas : "<<setprecision(6)<<(float)((clock()-start)/CLOCKS_PER_SEC)<<" : Dodano nowe zdarzenie."<<endl;
                    plik<<"Czas : "<<setprecision(6)<<(float)((clock()-start)/CLOCKS_PER_SEC)<<" : Dodano nowe zdarzenie."<<endl;

                    Event *evt = new Event(eventList->head->evt->next->time + eventList->head->evt->next->dt,"zdarzenie wywołane");
                    if(i%2==1)
                    {
                        evt->num = rand()%10;
                        evt->dt = 5.0 * ( (double)rand() / (double)RAND_MAX );
                    }
                    eventList->maxElements=ceil(sqrt(eventList->nrElements));
                    eventList->addEvent(evt);
                }
            }
            cout<<"Usuniecie zdarzenia : "<<setprecision(4)<<eventList->head->evt->next->time<<" : "<<eventList->head->evt->next->kindOfEvent<<endl;
            plik<<"Usuniecie zdarzenia : "<<setprecision(4)<<eventList->head->evt->next->time<<" : "<<eventList->head->evt->next->kindOfEvent<<endl;

            eventList->deleteFirst();
        }
    }

}
