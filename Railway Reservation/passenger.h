#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Passenger{
    public:
        int id;
        string name;
        int age;
        char gender;
        char berthPreference;
        string children;
        int PNR;
        vector<string> coPassengers;

        Passenger(int id, string name, int age, char gender, char berthPreference, string child);
        Passenger(const Passenger *passenger);
        void setPassengerDetails(int id, string name, int age, char gender, char berthPreference, string child);
};

Passenger::Passenger(int id, string name, int age, char gender, char berthPreference, string child)
{
    this->setPassengerDetails(id, name, age, gender, berthPreference, child);
}

Passenger::Passenger(const Passenger *passenger)
{
    this->id = passenger->id;
    this->name = passenger->name;
    this->age = passenger->age;
    this->berthPreference = passenger->berthPreference;
    this->children = passenger->children;
    this->gender = passenger->gender;
    this->PNR = passenger->PNR;
}

void Passenger::setPassengerDetails(int id, string name, int age, char gender, char berthPreference, string child)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->berthPreference = berthPreference;
    this->children= child;
}

#endif 