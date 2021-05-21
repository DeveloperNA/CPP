#include <iostream>
#include <vector>
#include "irctc.h"
#include "train.h"
#include "passenger.h"


using namespace std;


string checkForChild(char gender, int age)
{
    string child;
      if(gender == 'F' && age >= 18){
            char ch;
            cout << "Travelling with children?(Y/N): ";
            cin >> ch;
            if(ch == 'Y'){
                cout << " Enter the child name: ";
                cin >> child;
            }
        }
    return child;
}

int main()
{
    IRCTC irctc;

    Train *cheranExpress = new Train("Cheran", "12102", {"chennai", "coimbatore"}, "Sleeper");

    Passenger **passengersList;
    int n, pnr =1000, id=1;
    
    string name;
    int age, choice;
    char gender, berthPreference;

    // string c = "!AA";
    // passengersList = new Passenger*[95];

    // for(int i=0; i<95; i++){
    //     passengersList[i] = new Passenger(i, c, 19, 'M', 'U', "");
    //     cout << i;
    //     c[0]++;
    // }
    // irctc.bookTickets(passengersList, cheranExpress, 95, pnr);

    // free(passengersList);

    cout << "\n\t\t Welcome to Irctc\n\n";

    while(true){
        cout << "1. Book Tickets\n2. Cancel tickets\n3. Show Booked Tickets\n4. Show Available Tickets\n5. exit\n";
        cin >> choice;
        switch(choice){
            case 1: {
                cout << "Enter the no. of Passengers:";
                cin >> n;

                passengersList = new Passenger*[n+1];
                for(int i=0; i<n+1; i++){
                    passengersList[i] = nullptr;
                }

                for(int i=0; i<n; i++){
                    string child;
                    printf("\nEnter the details of Passenger %d\n:", i+1);
                    cout << "Name: ";
                    // cin >> name;
                    getline(cin >> ws, name);
                    cout << "Age: ";
                    cin >> age;
                    cout << "Gender(M/F): ";
                    cin >> gender;
                    child = checkForChild(gender, age);
                    cout << "Berth Preference(U /M /L): ";
                    cin >> berthPreference;
            
                    passengersList[i] = new Passenger(id, name, age, gender, berthPreference, child);
                    id++;
                }

                irctc.bookTickets(passengersList, cheranExpress, n, pnr);
                pnr++;
                irctc.printList(passengersList);
                break;
            }

            case 2: {
                int targetPnr, targetId;
                Passenger **list = NULL;
                cout << "Enter the PNR number to cancel tickets: ";
                cin >> targetPnr;
                
                list = irctc.filterTickets(cheranExpress, targetPnr);
                irctc.printList(list);
                if(list[0] == NULL){
                    cout << endl << "PNR not found" << endl;
                }
                else{
                    cout << "Provide the ticket id to cancel: ";
                    cin >> targetId;
                    int counter=0;
                    for(int i=0; list[i] != NULL; i++){
                        if(list[i]->id == targetId){
                            counter++;
                        }
                    }
                    if(counter ==0){
                        cout << endl << "Id unavailable" << endl;
                    }
                    else{
                        irctc.cancelTicket(cheranExpress, targetId);
                    }
                }
                break;
            }
            case 3:{
                cout << endl << "Occupied Tickets" << endl;
                irctc.showBookedTickets(cheranExpress);
                break;
            }
            case 4: {
                cout  << endl << "Tickets" << endl;
                irctc.showAvailableTickets(cheranExpress);
                break;
            }
            case 5: exit(0);
            break;
        }
       
    }

    return 0;
}