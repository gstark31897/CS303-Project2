#include "manager.h"
#include <iostream>

using namespace std;


int main()
{
    Manager manager;
    Customer *customer;

    while(true)
    {
        cout << "*****Main Menu*****" << endl;
        cout << "Log in (1)" << endl;
        cout << "Review Book (2)" << endl;
        cout << "Get Suggestions (3)" << endl;
        cout << "Exit (4)" << endl;
        cout << "Select One (1-4): " << flush;

        int choice = -1;
        cin >> choice;

        cin.clear();
        cin.ignore(10000, '\n');

        switch(choice)
        {
        case 1:
            {
                int id = -1;
                cout << "User ID: " << flush;
                cin >> id;
                customer = manager.getCustomer(id);
                if(customer == NULL)
                    cout << "ERROR: Invalid User ID" << endl;
                else
                    cout << "Welcome " << customer->getName() << endl;
            }
            break;
        case 2:
            break;
        case 3:
            {
                vector<Book*> suggestions;
                suggestions = manager.getRecomendations(customer->getId());
                cout << "Recomendations:" << endl;
                for(vector<Book*>::iterator it = suggestions.begin(); it != suggestions.end(); ++it)
                {
                    cout << (*it)->getDescription() << endl; 
                }
            }
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    }

    return 0;
}
