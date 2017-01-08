#include "MyList.hpp"
#include "Simulator.hpp"
#include "UI.hpp"
#include <iostream>
#include <math.h>
#include <ctime>

#define Tn 126.36

using namespace std;

void randomList(MyIndexList *a, int n=10, double max=2.0)
{
    srand( time( NULL ) );
    double t;
    for(int i=0; i<n; i++)
    {
        t = max * ( (double)rand() / (double)RAND_MAX );
        Event *evt = new Event(t,"zdarzenie losowe");
        if(i%2==1)
        {
            evt->num = rand()%5;
            evt->dt = max * ( (double)rand() / (double)RAND_MAX );
        }

        a->addEvent(evt);
    }
}

void testSymulatorNormal(int n=10, double max=5.0, double t=1.0)
{
    MyIndexList *a = new MyIndexList(t);

    randomList(a);

    a->show();

    Simulator *s = new Simulator(a);

    s->normalSimulation();

    a->show();
    a->showEvents();
}

void testSymulatorSecond(int n=10, double max=5.0, double t=1.0)
{
    MyIndexList *a = new MyIndexList(t);
    randomList(a,n,max);

    Simulator *s = new Simulator(a);

    s->secondSimulation(1.0);

    a->show();
}

/*
    Funkcja sprawdzajaca efektywność dokładania elementów
    do struktury. Badana teoretyczna złożoność to O(nsqrt(n))
    zamiast O(sqrt(n)) podanej w dok wstępnej ponieważ dodawanie
    jednego elementu daje nikly czas
*/
void testMyList(int n,int p,int interval,double time)
{
    float times[n/interval];
    MyIndexList *a = new MyIndexList();
    clock_t start;
    float t;

    for(int i = 0 ; i<n; i+=interval)
    {
        a->maxElements=ceil(sqrt(i));
        t=0.0f;
        for(int j=0; j<p; j++)
        {
            a->clear();
            start = clock();
            for(int k = 0; k<i; ++k)
            {
                a->addEvent(new Event(time,"zdarzenie"));
            }
            t+=(float)(clock()-start);
        }
        times[i/interval]=t/(interval*p);

    }
    for(int i=0; i<n/interval;i++)
        cout<<i*interval+1<<" "<<setprecision(3)<<times[i]<<" "<<setprecision(6)<<(times[i]*(n/2)*sqrt(n/2))/((i*interval+1)*sqrt(i*interval+1)*times[n/(2*interval)])<<endl;
}

void test(int n){
    double t=0.001;
    clock_t start;
    int ile = 0;
    int max=1;
    float asd;
    start = clock();
    for(int j = 0 ; j<n/2 ; ++j)
    {
        ile++;
            max = ceil(sqrt(ile));
        for(int m = 0 ; m <max ; m++)
         {
            t=0.0;
         }
    }
    asd = (float)(clock()-start)/1000;

    ile=0;max=1;
    for(int g = 1 ; g<=n; g+=1000)
    {
        start = clock();
        for(int j = 0; j<g ; j++)
        {
         ile++;
            max = ceil(sqrt(ile));
        for(int m = 0 ; m <max ; m++)
         {
            t=0.0;
         }

        }
 ile=0;max=1;
        float tn = (float)(clock()-start);
        cout<<g-1<<" "<<tn<<" "<<(tn*(n/2)*sqrt(n/2))/((g-1)*sqrt(g-1)*asd)<<" "<<asd<<endl;
    }

}

int main()
{
    MyIndexList *m = new MyIndexList();
    Simulator *s = new Simulator(m);
    UI *ui = new UI(m,s);
    ui->randomList(100,5.0);
    s->secondSimulation(1.0);
    m->show();
    m->showEvents();
    return 0;
}
