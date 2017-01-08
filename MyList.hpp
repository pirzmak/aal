#ifndef MYLIST_HPP_INCLUDED
#define MYLIST_HPP_INCLUDED
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

/*
Struktura do przetrzymywania zdarzeń. Zorganizowana w liste dwukierunkową.

time - czas wywołania zdarzenia
kindOfEvent - rodzaj zdarzenia
*/
struct Event{
    double time;
    string kindOfEvent;
    int num;
    double dt;
    Event *next;
    Event *prev;

    Event() : time(0.0), kindOfEvent("") {};
    Event(double t,string s) : time(t) , kindOfEvent(s) {};
    Event(double t,string s,int n,double d) : time(t) , kindOfEvent(s), num(n), dt(d) {};
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
    Key(double t) : time(t), empty(true), counter(1){ };
    Key(double t,Key *n, Key *p,Event *e) : time(t), empty(false), counter(1){
        evt = e;
        next = n;
        prev = p;
    };
};

/*
    Struktura implementująca dwupoziomową listę indeksowaną.

    head - pierwszy element w liście kluczy
    indexList - tablica indeksująca
    current - index atualnego klucza
    dT - różnica czasu
*/
struct MyIndexList{
    Key *head;
    Key **indexList;
    int maxElements;
    int nrElements;
    int current;
    int dT;

    MyIndexList(double t=1.0,int maxEl = 100);
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
