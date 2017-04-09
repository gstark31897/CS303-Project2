#include "manager.h"
#include <iostream>

using namespace std;


void clearCin()
{
    cin.clear();
    cin.ignore(10000, '\n');
}


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
        clearCin();

        switch(choice)
        {
        case 1:
            {
                int id = -1;
                cout << "User ID: " << flush;
                cin >> id;
                clearCin();
                customer = manager.getCustomer(id);
                if(customer == NULL)
                    cout << "ERROR: Invalid User ID" << endl;
                else
                    cout << "Welcome " << customer->getName() << endl;
            }
            break;
        case 2:
            {
                Book *book = NULL;
                int isbn = -1;
                while(true)
                {
                    cout << "Book ISBN: " << flush;
                    cin >> isbn;
                    clearCin();

                    book = manager.getBook(isbn);
                    if(book != NULL)
                        break;
                    cout << "Invalid ISBN" << endl;
                }

                int rating = -1;
                while(true)
                {
                    cout << "Book Rating (1-5): " << flush;
                    cin >> rating;
                    clearCin();

                    if(rating <= 5 && rating > 0)
                        break;
                    cout << "Invalid Rating" << endl;
                    
                }

                manager.rateBook(customer, isbn, rating); 
            }
            break;
        case 3:
            {
                vector<Book*> suggestions;
                suggestions = manager.getRecomendations(customer);
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
