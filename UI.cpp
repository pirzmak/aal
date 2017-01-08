#include"UI.hpp"


void UI::start()
{
    int a;
    cout<<"Symulator z czasem dyskretnym. Zdarzenia przetrzymywane w liście podwójnie indeksowanej\n"<<
        "Opcje : \n 1.Testowanie listy\n 2.Testowanie Symulacji\n 0.Koniec\n";
    while(1)
    {
        cin>>a;
        if(a==0||a==1||a==2)
            break;
        cout<<"Bledne dane. Sprobuj jeszcze raz"<<endl;
    }
    switch(a)
    {
    case 1:
        testList();
        break;
    case 2:
        testSimulator();
        break;
    }

}

void UI::testList()
{
    int a;
    cout<<"Testowanie List.\n"<<" 1.Testowanie dodawania elementu (dodawanie elementów z danych z konsoli)\n"<<
        " 2.Zapelnienie listy danymi losowymi\n 3.Zapełnienie listy danymi z pliku\n"
        " 4.Analiza czasu dodawania elementu w zależności od ilości elementów w liście\n 0.Wroc\n";
    while(1)
    {
        cin>>a;
        if(a>=0&&a<=4)
            break;
        cout<<"Bledne dane. Sprobuj jeszcze raz"<<endl;
    }
    switch(a)
    {
    case 0:
        start();
        break;
    case 1:
        testAddList();
        show();
        break;
    case 2:
        testRandomAddList();
        show();
        break;
    case 3:
        testListFromFile();
        show();
        break;
    case 4:
        testTime();
        break;
    }
}

void UI::testTime()
{
    int n;
    int p;
    int interval;

    cout<<"Testowanie czasu dodawania elementu do listy.\n"<<" Podaj liczbe elementow : ";
    cin>>n;
    cout<<" Podaj co ile elementow badany ma byc czas : ";
    cin>>interval;
    cout<<" Podaj liczbe powtorzen testu : ";
    cin>>p;

    testMyList(n,p,interval,0.01);
}

void UI::testAddList()
{
    int n;
    float t;
    string k;
    cout<<"Testowanie dodawania elementu do listy.\n"<<" Podaj liczbe elementow : ";
    cin>>n;
    while(n--)
    {
        cout<<" Czas : ";
        cin>>t;
        cout<<" Typ zdarzenia : ";
        cin>>k;
        eventList->addEvent(new Event(t,k));
    }

}

void UI::testRandomAddList()
{
    int n;
    double max;
    cout<<"Losowe dodawania elementu do listy.\n"<<" Podaj liczbe elementow : ";
    cin>>n;
    cout<<" Podaj maksymalny czas zdarzenia : ";
    cin>>max;
    eventList->maxElements = ceil(sqrt(n));
    randomList(n,max);

}

void UI::randomList(int n, double max)
{
    srand( time( NULL ) );
    double t;
    for(int i=0; i<n; i++)
    {
        t = max * ( (double)rand() / (double)RAND_MAX );
        Event *evt = new Event(t,"zdarzenie losowe");
        if(i%2==1)
        {
            evt->num = rand()%10;
            evt->dt = max * ( (double)rand() / (double)RAND_MAX );
        }

        eventList->addEvent(evt);
    }
}

void UI::testSimulator()
{
    int a;
    float t;
    cout<<"Testowanie Symulatora.\n"<<" 1.Zapelnij liste danymi losowymi\n"<<
        " 2.Zapelnij liste danymi z pliiku\n 3.Symulacja normalna\n"
        " 4.Symulacja ze zdarzeniami wywolujacymi\n 0.Wroc\n";
    while(1)
    {
        cin>>a;
        if(a>=0&&a<=4)
        {
            if((a==3||a==4)&&eventList->empty())
                cout<<"Lista pusta - zapelnij liste"<<endl;
            else
                break;
        }
        else
            cout<<"Bledne dane. Sprobuj jeszcze raz"<<endl;
    }
    switch(a)
    {
    case 0:
        start();
        break;
    case 1:
        testRandomAddList();
        testSimulator();
        break;
    case 2:
        testListFromFile();
        testSimulator();
        break;
    case 3:
        simulator->normalSimulation();
        show();
        break;
    case 4:
        cout<<"Podaj czas symulacji : ";
        cin>>t;
        simulator->secondSimulation(t);
        show();
        break;
    }
}


void UI::show()
{
    int a;
    cout<<"Prezentacja wynikow\n 1.Lista nadrzedna\n 2.Lista zdarzeń\n 3.Oba\n";
    while(1)
    {
        cin>>a;
        if(a==1||a==2||a==3)
            break;
        cout<<"Bledne dane. Sprobuj jeszcze raz"<<endl;
    }
    switch(a)
    {
    case 1:
        cout<<"Lista podrzedna\nCzas końcowy podprzedziału | ilosc elementów w podprzedziale\n";
        eventList->show();
        break;
    case 2:
        cout<<"Lista zdarzen\nCzas zdarzenia | typ zdarzenia\n";
        eventList->showEvents();
        break;
    case 3:
        cout<<"Czas końcowy podprzedziału | ilosc elementów w podprzedziale\n";
        eventList->show();
        cout<<"Czas zdarzenia | typ zdarzenia\n";
        eventList->showEvents();
        break;
    }
}

void UI::testListFromFile()
{
    string a;
    cout<<"Podaj nazwe pliku :"<<endl;
    cin>>a;
    while(!loadListFromFile(a))
    {
        cout<<"Zla nazwa pliku. Sprobuj jeszcze raz"<<endl;
        cin>>a;
    }
}

bool UI::loadListFromFile(string name)
{
    fstream plik;
    plik.open( name, ios::in | ios::out );

    if( plik.good() == false )
    {
        std::cout << "Load File Error!" << std::endl;
        return false;
    }
    while(!plik.eof())
    {
        Event *evt = new Event();
        plik >> evt->time >> evt->kindOfEvent >> evt->num >> evt->dt ;
        eventList->addEvent(evt);
    }
    plik.close();
    return true;
}

/*
    Funkcja sprawdzajaca efektywność dokładania elementów
    do struktury. Badana teoretyczna złożoność to O(nsqrt(n))
    zamiast O(sqrt(n)) podanej w dok wstępnej ponieważ dodawanie
    jednego elementu daje nikly czas
*/
void UI::testMyList(int n,int p,int interval,double time)
{
    float times[n/interval];
    MyIndexList *a = new MyIndexList();
    clock_t start;
    float t;
    float load = 0.0f;
    fstream plik;
    plik.open( "log.txt", ios::out );

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
        load += 100/(n/interval);
        if(load>1)
        {
            cout<<"|";
            load--;
        }
        times[i/interval]=t/(interval*p);

    }
    for(int i=0; i<n/interval; i++){
        cout<<i*interval+1<<" "<<setprecision(3)<<times[i]<<" "<<setprecision(6)<<(times[i]*(n/2)*sqrt(n/2))/((i*interval+1)*sqrt(i*interval+1)*times[n/(2*interval)])<<endl;
        plik<<i*interval+1<<" "<<setprecision(3)<<times[i]<<" "<<setprecision(6)<<(times[i]*(n/2)*sqrt(n/2))/((i*interval+1)*sqrt(i*interval+1)*times[n/(2*interval)])<<endl;
    }
}

