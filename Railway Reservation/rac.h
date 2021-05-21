#ifndef RAC_H
#define RAC_H

#include <iostream>
#include "passenger.h"

using namespace std;


class RAC{
    private:
    struct RACList{
        Passenger *passenger;
        RACList *next;
    };
    RACList *head, *last;
    
    public:
    int count;
    RAC();
    Passenger* getHead();
    void insertToRacList(Passenger *p);
    Passenger **getPassengersListByPNR(int pnr);
    Passenger* removeFromRacList();
    bool remove(string field, string value);
    Passenger *getPassenger(string field, string value);
    void viewRac();
};

void RAC::insertToRacList(Passenger *p)
{
    if(this->head == NULL){
        RACList *n = new RACList();
        n->passenger = p;
        n->next = NULL;
        this->head = n;
        this->last = n;
    }
    else{
        RACList *n = new RACList();
        n->passenger = p;
        n->next = NULL;
        this->last->next = n;
        this->last = n;
    }

    this->count++;
}

Passenger* RAC::removeFromRacList()
{
    RACList *t = this->head;
    RACList *d;

    if(this->head == this->last){
        d = this->head;
        this->head = this->last = NULL;
        this->count =0;
        free(d);
    }
    else if(this->head != NULL){
        d = this->head;
        this->head = this->head->next;
        free(d);
        this->count--;
    }

    return t!= NULL? t->passenger: NULL;
}


void RAC::viewRac()
{
    cout << "\n\nviewRAC\n\n";
    RACList *n = this->head;
    for(int i=0; i<this->count; i++){
        cout << n->passenger->name << "\t";
        n = n->next;
    }
    cout << endl;
}

Passenger** RAC::getPassengersListByPNR(int pnr)
{
    cout << "rac list" << endl;
    if(this->head == NULL){
        return nullptr;
    }
    else{
        RACList *temp;
        Passenger **list = new Passenger*[19];
        for(int i=0; i<19; i++){
            list[i] = nullptr;
        }
        int i=0;
        for(temp = this->head; temp != NULL; temp = temp->next)
        {   
            if(temp->passenger->PNR == pnr)
                list[i++] = temp->passenger;
        }
        cout << endl << "rac i " << i << endl;
        return list;
    }
}


bool RAC::remove(string field, string value)
{
    cout << endl << "value :" <<  value << endl;
    int id = stoi(value);
    RACList *temp, *d, *prv = NULL;

    for(temp = this->head; temp != NULL; temp = temp->next){
        if(temp->passenger->id == id){
            if(prv == NULL){
                this->removeFromRacList();
                return true;
            }
            else if(temp == this->last){
                prv->next = NULL;
                this->last = prv;
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



RAC::RAC()
{
    this->count = 0;
    this->head = NULL;
    this->last = NULL;
}
#endif 