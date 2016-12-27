#include "MyList.hpp"
#include "Simulator.hpp"
#include <iostream>
#include <math.h>
#include <ctime>

#define Tn 126.36

using namespace std;

void randomList(MyIndexList *a, int n=10, double max=5.0)
{
    srand( time( NULL ) );
    double t;
    for(int i=0; i<n; i++)
    {
        t = max * ( (double)rand() / (double)RAND_MAX );
        Event *evt = new Event(t,"zdarzenie losowe");
        if(i%2==1)
        {
            evt->num = 1;
            evt->dt = max * ( (double)rand() / (double)RAND_MAX );
        }

        a->addEvent(evt);
    }
}

void testSymulatorNormal(int n=10, double max=5.0, double t=1.0)
{
    MyIndexList *a = new MyIndexList(t);
    randomList(a,n,max);

    a->show();

    Simulator *s = new Simulator(a);

    s->normalSimulation();

    a->show();
}

void testSymulatorSecond(int n=10, double max=5.0, double t=1.0)
{
    MyIndexList *a = new MyIndexList(t);
    randomList(a,n,max);

    Simulator *s = new Simulator(a);

    s->secondSimulation(1.0);

    a->show();
}

void testMyList(int n)
{
    MyIndexList *a = new MyIndexList();
    double t=0.001;
    clock_t start;

    float asd;
    start = clock();
        for(int j = 1 ; j<n*5000 ; ++j)
        {
            t += 0.05;
            a->addEvent(new Event(t,"zdarzenie"));
            if(t>=1.0)
                t= 0.001;

        }
    asd = (float)(clock()-start)/1000;

    a->clear();

    for(int i = 1 ; i<n ; ++i)
    {
        start = clock();
        for(int j = 1 ; j<10000 ; ++j)
        {
            t += 0.05;
            a->addEvent(new Event(t,"zdarzenie"));
            if(t>=1.0)
                t= 0.001;

        }
        float tn = (float)(clock()-start)/1000;


        cout<<i*10000<<" "<<tn<<" "<<(tn*sqrt(n*50000))/(sqrt(i*10000)*asd)<<" "<<asd<<endl;

    }



    //a->show();
}

int main()
{
    cout << "Hello world!" << endl;

    testMyList(100);


    return 0;
}
