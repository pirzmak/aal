#ifndef MYLIST_HPP_INCLUDED
#define MYLIST_HPP_INCLUDED
#include <iostream>

using namespace std;

/*
Struktura do przetrzymywania zdarzeń. Zorganizowana w liste dwukierunkową.

time - czas wywołania zdarzenia
kindOfEvent - rodzaj zdarzenia
*/
struct Event{
    double time;
    string kindOfEvent;
    double secondTime;
    int num;
    double dt;
    Event *next;
    Event *prev;

    Event() : time(0.0), kindOfEvent("") {};
    Event(double t,string s) : time(t) , kindOfEvent(s) {};
    Event(double t,string s,Event *n, Event *p) : time(t) , kindOfEvent(s) {
        next = n;
        prev = p;
    };
};

/*
Struktura do przetrzymywania kluczy listy nadrzędnej. Zorganizowana w liste dwukierunkową.

time - czas wywołania zdarzenia
evt - wskaźnik na zdarzenie o danym czasie
empty - zmienna określająca czy klucz jest pusty
counter - liczba zdarzeńw podliście
*/
struct Key{
    double time;
    Event *evt;
    bool empty;
    int counter;
    Key *next;
    Key *prev;

    Key() : time(0.0), empty(false), counter(0){ };
    Key(double t) : time(t), empty(true), counter(0){ };
    Key(double t,Key *n, Key *p,Event *e) : time(t), empty(false), counter(1){
        evt = e;
        next = n;
        prev = p;
    };
};

/*
Struktura implementująca dwupoziomową listę indeksowaną.

*/
class MyIndexList{
    public:
    //pierwszy element w liście kluczy
    Key *head;

    //tablica indeksująca
    Key **indexList;

    //index atualnego klucza
    int current;
    int dT;

    MyIndexList(double t=1.0);
    void addEvent(Event *evt);
    int index(double time);
    void adjust(Key *list);
    void show();
    void showEvents();
    void insertToList(Event *evt, Event *x);
    void deleteFirst();
    void clear();
    bool empty();

};


#endif // MYLIST_HPP_INCLUDED
