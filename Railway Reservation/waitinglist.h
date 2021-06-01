
#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <iostream>
#include "passenger.h"

using namespace std;

class WaitingTickets{
    private:

    struct WaitingList{
        Passenger *passenger;
        WaitingList *next;
    };
    struct WaitingList *head, *last;
   
    public:
    int count;
    WaitingTickets();
    void insertToWaitingList(Passenger* passenger);
    Passenger **getPassengersListByPNR(int pnr);
    Passenger* removeFromWaitingList();
    bool remove(string field, string value);
    void viewWaitingList();
};

WaitingTickets::WaitingTickets()
{
    this->count =0;
    this->head = NULL;
    this->last = NULL;
}

void WaitingTickets::insertToWaitingList(Passenger* passenger)
{
    struct WaitingList *n = new WaitingList();
    n->passenger = passenger;
    n->next = NULL;
    
    if(this->head == NULL){
        this->head = n;
        this->last = n;
    }
    else{
        this->last->next = n;
        this->last = n;
    }
    this->count++;
}

Passenger* WaitingTickets::removeFromWaitingList()
{
    WaitingList *t = this->head;
    WaitingList *d;
    if(this->head == this->last){
        d = this->head;
        this->head = this->last = NULL;
        free(d);
        this->count = 0;
    }
    else if(this->head != NULL){
        d = this->head;
        this->head = this->head->next;
        free(d);
        this->count--;
    }
    return t != NULL ? t->passenger : NULL;
}
Passenger **WaitingTickets::getPassengersListByPNR(int pnr)
{
    if(this->head == NULL){
        return nullptr;
    }
    else{
        WaitingList *temp;
        Passenger **list = new Passenger*[11];
        for(int i=0; i<11; i++){
            list[i] = nullptr;
        }
        int i=0;
        for(temp = this->head; temp != NULL; temp = temp->next)
        {   
            if(temp->passenger->PNR == pnr){
                list[i++] = temp->passenger;
            }
        }
        return list;
    }
}
bool WaitingTickets::remove(string field, string value)
{
    // cout << endl << "value :" <<  value << endl;
    int id = stoi(value);
    WaitingList *temp, *d, *prv = NULL;

    for(temp = this->head; temp != NULL; temp = temp->next){
        if(temp->passenger->id == id){
            if(prv == NULL){
                this->removeFromWaitingList();
                return true;
            }
            else if(temp == this->last){
                this->last = prv;
                this->last->next = NULL;
                free(temp);
                this->count--;
                return true;
            }
            else{
                d = temp;
                prv->next = temp->next;
                free(d);
                this->count--;
                return true;
            }
        }
        prv= temp;
    }
    return false;
}

void WaitingTickets::viewWaitingList()
{
    struct WaitingList *n = this->head;
    cout << endl << "Waiting list :" << endl << endl;

 
    for(int i=0; i<10; i++){
        if(i < this->count){
            cout << n->passenger->id << "\t";
            n= n->next;
        }
        else{
            cout << "F ";
        }
    }
    cout << "\n\n";
}

#endif