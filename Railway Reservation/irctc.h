#ifndef IRCTC_H
#define IRCTC_H

#include <iostream>
#include "passenger.h"
#include "train.h"

using namespace std;

class IRCTC{
    private:
        struct TrainList{
            Train *train;
            TrainList* next;
        };
        
        TrainList *head;
    public:
        void addTrain(Train *obj); 
        void bookTickets(Passenger **passengers, Train *train, int count, int pnr);
        void cancelTicket(Train *train, int id);
        void printList(Passenger **list);
        void showAvailableTickets(Train *train);
        void showBookedTickets(Train *train);
        Passenger** filterTickets(Train *train, int pnr);
};

void IRCTC::bookTickets(Passenger **passengers, Train *train, int count, int pnr)
{
    for(int i=0; i<count; i++){
        string berth;
        berth += passengers[i]->berthPreference;
        int *ind = (train->tickets->count >= 63) ? new int[2]{-1, -1} : train->tickets->getAvailable("berth", berth);
       
        if(ind[0]>-1 && ind[1]>-1){
            train->allotTicket(passengers[i], ind, pnr);    
        }
        else{
            if((!passengers[i]->children.empty() && passengers[i]->gender == 'F') || (passengers[i]->age >=60) &&(passengers[i]->berthPreference != 'L')){
                int *ind = (train->tickets->count > 63)? new int[2]{-1, -1} : train->tickets->getAvailable("berth", "L");
                if(ind[0] > -1 && ind[1] > -1){
                    train->allotTicket(passengers[i], ind, pnr);
                }
            }
            else{
                int *ind = (train->tickets->count > 63)? new int[2]{-1, -1} : train->tickets->getEmpty();
                if(ind[0]>-1 && ind[1]>-1){
                    train->allotTicket(passengers[i], ind, pnr);
                }
                else if(train->Rac->count < 18){
                    train->allotRac(passengers[i], pnr);
                }
                else if(train->waitingTickets->count < 10){
                    train->allotWaiting(passengers[i], pnr);
                }
                else{
                    cout << "Unable to book ticket for passenger : " << passengers[i]->name << endl;
                }
            }
        }
    }
}

Passenger** IRCTC::filterTickets(Train *train, int pnr)
{
    Passenger **t = train->tickets->getPassengersListByPNR(pnr);
    Passenger **r = train->Rac->getPassengersListByPNR(pnr);
    Passenger **w = train->waitingTickets->getPassengersListByPNR(pnr);
    Passenger **list = new Passenger*[91];
    int i=0;

    for(i=0; t[i] != nullptr; i++){
        list[i] = t[i];
        // // cout << t[i]->name << "\t"
        // cout << list[i]->name << "\t";
        // cout << i << endl;
    }

    if(r != NULL){
        for(int j=0; r[j] != nullptr; j++){
            cout << i << "\t";
            list[i++] = r[j];
        }
    }

    if(w != NULL){
        for(int k=0; w[k] != nullptr; k++){
            cout << i << "\t";
            list[i++] = w[k];
        }
    }

    for(;i<91;i++)
    {
        list[i] = nullptr;
    }

    return list;
}

void IRCTC::printList(Passenger **list)
{
    for(int i=0; list[i]!= nullptr; i++){
        cout << endl << list[i]->id << "\t" << list[i]->name << "\t" << list[i]->berthPreference  << "\t" << list[i]->PNR << endl;
    }
}

void IRCTC::cancelTicket(Train *train,int id)
{
    string str = to_string(id);
    int *ind ;
    cout << endl << str << endl;
    ind = train->tickets->getAvailable("id", str);

    if(ind[0] > -1 && ind[1] > -1){
        cout << endl << "removing ";
        cout << (*train->tickets)(ind[0], ind[1])->name  << "..." << endl;
        train->tickets->remove(ind);
        if(train->Rac->count > 0){

            Passenger *p = train->Rac->removeFromRacList();
            train->tickets->insert(p, ind);
            
            if(train->waitingTickets->count > 0){
                p = train->waitingTickets->removeFromWaitingList();
                train->Rac->insertToRacList(p);
            }
        }
    }
    else{
        cout << "RAC removal" << endl;
        bool isRemoved = train->Rac->remove("id", str);
        if(isRemoved){
            if(train->waitingTickets->count > 0){
                Passenger *p = train->waitingTickets->removeFromWaitingList();
                train->Rac->insertToRacList(p);
            }
        }
        else{
            cout << "WaitingList removal" << endl;
            bool isRemoved = train->waitingTickets->remove("id", str);
            if(!isRemoved){
                cout << " Id not found " << endl;
            }
        }
    }
    cout << endl << "Successfully removed" << endl;
}

void IRCTC::showAvailableTickets(Train *train)
{
    train->tickets->viewAllEmpty();
    cout << endl << "Total Number of Tickets Unoccupied are : " << 63 - train->tickets->count << endl << endl;
}

void IRCTC::showBookedTickets(Train *train)
{
    train->tickets->viewTickets();
    cout << endl << "Total Number of Tickets Occupied are: " << train->tickets->count << endl;
}

#endif