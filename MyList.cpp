#include "MyList.hpp"
#include <math.h>

#define INDEXNUM 4

int MAXNRELEMENTS = 0; //maksymalna liczba elementów wyznaczana na podstawie liczby elementów
int NRELEMENTS = 0; //liczba elementów

MyIndexList::MyIndexList(double t)
{
    current = 0;
    dT = t;
    head = new Key(-1.1);
    head->evt = new Event(-1.1,"");

    indexList = new Key*[INDEXNUM];

    //do listy Key
    indexList[0]=new Key(dT);
    indexList[0]->prev=head;
    head->next=indexList[0];
    //do listy eventow
    indexList[0]->prev=head;
    indexList[0]->evt = new Event(dT,"Solid");   //dodanie sztcznego eventu
    indexList[0]->evt->prev = head->evt;
    head->evt->next = indexList[0]->evt;

    for(int i=1; i<INDEXNUM-1; ++i)
    {
        //do listy Key
        indexList[i]= new Key((i+1)*dT);
        indexList[i]->prev = indexList[i-1];
        indexList[i-1]->next = indexList[i];
        //do listy eventow
        indexList[i]->evt = new Event((i+1)*dT,"Solid");       //dodanie sztucznego eventu
        indexList[i]->evt->prev = indexList[i-1]->evt;  //ustawinie wskaznikow
        indexList[i-1]->evt->next = indexList[i]->evt;  //ustawinie wskaznikow
    }

    //do listy Key
    indexList[INDEXNUM-1]= new Key(999999.9);
    indexList[INDEXNUM-1]->next=head;
    indexList[INDEXNUM-1]->prev=indexList[INDEXNUM-2];
    indexList[INDEXNUM-2]->next=indexList[INDEXNUM-1];
    head->prev=indexList[INDEXNUM-1];
    //do listy eventow
    indexList[INDEXNUM-1]->evt = new Event(999999.9,"Solid");
    indexList[INDEXNUM-1]->evt->next=head->evt;
    indexList[INDEXNUM-1]->evt->prev=indexList[INDEXNUM-2]->evt;
    indexList[INDEXNUM-2]->evt->next=indexList[INDEXNUM-1]->evt;
    head->evt->prev=indexList[INDEXNUM-1]->evt;
}

int MyIndexList::index(double time)
{
    double tmp1 = indexList[current]->time - dT; // dolna granica pierwszego przedziału
    double tmp2 = tmp1 + dT*(INDEXNUM-1);   //dolnagranica ostatniego przedziału


    if(time-tmp1<0)
        return current;
    if(time <= tmp2)
        return ((int)((time-tmp1)/dT) + current)%(INDEXNUM-1);

    return INDEXNUM-1;
}


/*
  Dodanie zdarzenia do listy indeksowanej. Jako argument przyjmuje zmienna Event.
  wykorzystuje funkcje index do obliczenia indeksu klucza wstawiania zdarzenia i
  funkcje adjust do ewentualnego wyrownania listy z kluczami
*/
void MyIndexList::addEvent(Event *evt)
{
    NRELEMENTS++;
    MAXNRELEMENTS = ceil(sqrt(NRELEMENTS));

    Key *x = indexList[index(evt->time)];

    while(x->time >= evt->time)
        x=x->prev;
    x=x->next;
    insertToList(evt, x->evt);
    //wyrównanie
    if(x->counter < MAXNRELEMENTS)
        x->counter++;
    else
        adjust(x);
}

/*
  Funkcja wyrównująca liczbę zdarzeń w kazdym kluczu
*/
void MyIndexList::adjust(Key *list)
{
    Key *kp = list->prev;
    Event *e = kp->evt->next;

    if(kp->empty || kp->counter == MAXNRELEMENTS)
    {
        //wstawienie nowego klucza
        kp = new Key();
        kp->prev = list->prev;
        kp->next = list;
        list->prev->next=kp;
        list->prev = kp;
        kp->counter = 0;
    }

    kp->counter += 1;
    kp->evt = e;
    kp->time = e->time;
}

/*
    Włożenie zdarzenia do listy na odpowiedznie miejsce
*/
void MyIndexList::insertToList(Event *evt,Event *x)
{

    while(x->time >= evt->time)
        x=x->prev;
    evt->prev = x;
    evt->next = x->next;
    x->next = evt;
    evt->next->prev = evt;
}

void MyIndexList::deleteFirst()
{
    Event *tmp = head->evt->next;

    head->evt->next->prev=head->evt;
    head->evt->next = head->evt->next->next;

    cout<<"Delete : "<<tmp->time<<" : "<<tmp->kindOfEvent<<endl;

    if(tmp->kindOfEvent!="Solid"){
        NRELEMENTS--;
    }
    delete tmp;

    head->next->counter--;

    if(head->next->counter<=0)
    {
        Key *k = head->next;

        head->next->next->prev = head;
        head->next = head->next->next;
        if(k->empty)
        {
            //przesuniecie zdarzen pustych
            k->time=k->time + dT*(INDEXNUM-1);

            Key *pom = head->prev;

            while(pom->time>=k->time)
                pom=pom->prev;

            pom=pom->next;

            k->prev=pom->prev;
            k->next=pom;

            pom->prev->next=k;
            pom->prev=k;

            k->evt = new Event(k->time,"Solid");
            k->counter=0;

            insertToList(k->evt,head->prev->evt);

            if(k->evt->time>=head->prev->evt->prev->time)
            {
                k->counter=head->prev->counter;
                head->prev->counter=0;
            }
            current = (current+1)%(INDEXNUM-1);
        }
        else
        {
            delete k;
        }
    }

}

void MyIndexList::show()
{

    Key *x = head->next;

    while(x!=head)
    {
        cout<<x->time<<" : "<<x->counter<<" "<<x->empty<<endl;
        x=x->next;
    }

    cout<<NRELEMENTS<<endl;
}

void MyIndexList::clear()
{

    Event *evt = head->evt->next;
    Event *tmp;

    while(evt!=head->evt)
    {
        tmp=evt;
        evt=evt->next;
        if(tmp->kindOfEvent!="Solid")
        {
            tmp->next->prev=tmp->prev;
            tmp->prev->next=tmp->next;
            delete tmp;

        }
    }

    Key *key = head->next;
    Key *tmpK;

    while(key!=head)
    {
        tmpK=key;
        tmpK->counter = 0;
        key=key->next;
        if(!tmpK->empty)
        {
            tmpK->next->prev=tmpK->prev;
            tmpK->prev->next=tmpK->next;
            delete tmpK;

        }
    }

    NRELEMENTS=MAXNRELEMENTS=0;
}

void MyIndexList::showEvents()
{

    Event *x = head->evt->next;

    while(x!=head->evt)
    {
        cout<<x->time<<" : "<<x->kindOfEvent<<endl;
        x=x->next;
    }
}

bool MyIndexList::empty()
{
    return !NRELEMENTS;
}
