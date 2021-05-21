#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
using namespace std;

class Route{
    public:
    string from;
    string destination;

    Route* getRoute();
    void setRoute();
};

#endif 