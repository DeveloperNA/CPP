#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include "passenger.h"
#include <string>

class Ticket{
    private:
    Passenger ***tkts;

    public:
    int count;

    Ticket();
    void insert(Passenger *p, int* ind);
    void remove(int *ind);
    int *getAvailable(string field, string value);
    int *getEmpty();
    void viewTickets();
    void viewAllEmpty();
    Passenger **getPassengersListByPNR(int pnr);
    Passenger* operator()(int row, int column);
};


Ticket::Ticket()
{
    this->tkts = new Passenger**[9];
    this->count = 0;

    for(int i=0; i<9; i++){
        this->tkts[i] = new Passenger*[7];
        for(int j=0; j<7; j++){
            this->tkts[i][j] = NULL;
        }
    }

      
    cout << endl;
}

void Ticket::insert(Passenger *passenger, int *ind)
{
    this->tkts[ind[0]][ind[1]] = new Passenger(passenger);
    this->count++;  
}

void Ticket::remove(int *ind)
{
    free(this->tkts[ind[0]][ind[1]]);
    this->tkts[ind[0]][ind[1]] = nullptr; 
    this->count--;
}

Passenger* Ticket::operator()(int row, int column)
{
  
    if(row > 9 || column > 7){
        return NULL;
    }
    // return &this->tkts[row][column];
    return this->tkts[row][column];

}

int* Ticket::getAvailable(string field, string value)
{
    int *indices = new int[2];
    indices[0] = indices[1] = -1;

    if(field == "berth"){
        char berth = value[0];
        if(berth == 'L'){
            for(int i=0; i<9; i++){
                for(int j=0; j<2; j++){
                    if(this->tkts[i][j] == nullptr){
                        indices[0] = i;
                        indices[1] = j;
                        return indices; 
                    }
                }
            }
        }
        else if(berth == 'M'){
            for(int i=0; i<9; i++){
                for(int j=2; j<4; j++){
                    if(this->tkts[i][j] == nullptr){
                        indices[0] = i;
                        indices[1] = j;
                        return indices;
                    }
                }
            }
        }
        else if(berth == 'U'){
            for(int i=0; i<9; i++){
                for(int j=4; j<7; j++){
                    if(this->tkts[i][j] == nullptr){
                        indices[0] = i;
                        indices[1] = j;
                        return indices;
                    }
                }
            }
        }      
    }
    else if(field == "id"){
        int id = stoi(value);
        cout << endl << "Id to be deleted is " << id << endl;
        for(int i=0; i<9; i++){
            for(int j=0; j<7; j++){
                if(this->tkts[i][j] != NULL && this->tkts[i][j]->id == id){
                    indices[0] = i;
                    indices[1] = j;
                    return indices;
                }
            }
        }

    }

    return indices;

}

Passenger** Ticket::getPassengersListByPNR(int pnr)
{
    cout << " ticket list" << endl;
    Passenger **list = new Passenger*[64];
    int k=0;
    for(int i=0; i<64; i++){
        list[i] = nullptr;
    }

    for(int i=0; i<9; i++){
        for(int j=0; j<7; j++){
            // cout << i << j << endl;
            // cout << "entered pnr:" << pnr << endl;

            if(this->tkts[i][j] != nullptr && this->tkts[i][j]->PNR == pnr){
                // cout << endl << "Match" << endl;
                list[k++] = this->tkts[i][j];
            }
        }
    }
    return list;
}

int* Ticket::getEmpty()
{
    int *res = new int[2];
    res[0] = res[1] = -1;

    for(int i=0; i<9; i++){
        for(int j=0; j<7; j++){

            if(this->tkts[i][j] == nullptr){
                res[0] = i;
                res[1] = j;
                return res;
            }
        }
    }

    return res;
}

void Ticket::viewTickets()
{

     for(int i=0; i<9; i++){
        for(int j=0; j<7; j++){
            cout << i << j;      
            if(this->tkts[i][j] ==nullptr)
                cout << "F" << "\t";
            else {
                cout << this->tkts[i][j]->name << "\t";
            }
        }
        cout << endl;
    }

}

void Ticket::viewAllEmpty()
{
    for(int i=0; i<9; i++){
        for(int j=0; j<7; j++){
            if(this->tkts[i][j] == nullptr){
                cout << i << j << "\t";
            }
            else
                cout << "*\t";
        }
        cout << endl;
    }
    
}
#endif 