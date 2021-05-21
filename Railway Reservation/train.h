#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include "route.h"
#include "rac.h"
#include "waitinglist.h"
#include "ticket.h"

using namespace std;

class Train{
    public:
        string name;
        string id;
        Route route;
        string classes;
        Ticket *tickets;  
        RAC *Rac;
        WaitingTickets *waitingTickets;

        Train(string name, string id, Route route, string classes);
        void setDetails(string name, string id, Route route, string classes);

        
        void showAvailableTickets();
        void showBookedTickets();   
        // Passenger **getPassenger(int pnr);
        void allotTicket(Passenger *passenger, int* ind, int pnr);
        void allotRac(Passenger *paasenger, int pnr);
        void allotWaiting(Passenger *passenger, int pnr);
};

Train::Train(string name, string id, Route route, string classes)
{
    setDetails(name, id, route, classes);
    this->tickets = new Ticket();
    this->Rac = new RAC();
    this->waitingTickets = new WaitingTickets();
}

void Train::setDetails(string name, string id, Route route, string classes)
{
    this->name = name;
    this->id = id;
    this->route = route;
    this->classes = classes;
}



void Train::showAvailableTickets()
{   
    this->tickets->viewTickets();
    this->Rac->viewRac();
    this->waitingTickets->viewWaitingList(); 
}


void Train::allotTicket(Passenger *passenger, int* ind, int pnr)
{
    cout << endl <<  "ticket allocation" << endl;
    passenger->PNR = pnr;
    this->tickets->insert(passenger, ind);
}

void Train::allotRac(Passenger *passenger, int pnr)
{
    cout << endl << "RAC Ticket" << endl;
    passenger->PNR = pnr;
    this->Rac->insertToRacList(passenger);
}

void Train::allotWaiting(Passenger *passenger, int pnr)
{
    cout << endl << "Waiting Ticket" << endl;
    passenger->PNR = pnr;
    this->waitingTickets->insertToWaitingList(passenger);
}



#endif 