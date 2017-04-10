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
        cout << "Search Books (2)" << endl;
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
                while(true)
                {
                    cout << "*****Book Search*****" << endl;
                    cout << "By ISBN (1)" << endl;
                    cout << "By Description (2)" << endl;
                    cout << "Main Menu (3)" << endl;
                    cout << "Select One (1-3): " << flush;

                    cin >> choice;
                    clearCin();

                    cout << "Enter Query: " << flush;
                    string line;
                    getline(cin, line);

                    vector<Book*> books;
                    bool gotoMain = false;
                    switch(choice)
                    {
                    case 1:
                        books = manager.getBooksByIsbn(line);
                        break;
                    case 2:
                        books = manager.getBooksByDescription(line);
                        break;
                    case 3:
                        gotoMain = true;
                        break;
                    default:
                        cout << "Invalid Choice" << endl;
                        continue;
                    }

                    if(gotoMain)
                        break;

                    while(true)
                    {
                        cout << "*****Result*****" << endl;
                        for(long i = 0; i < books.size(); ++i)
                        {
                           cout << books[i]->getIsbn() << ':' << books[i]->getDescription() << " (" << i + 1 << ')' << endl;
                        }
                        cout << "New Query (0)" << endl;
                        cout << "Select One (0-" << books.size() << "): " << flush;

                        long selection = -1;
                        cin >> selection;
                        clearCin();

                        bool exitResult = false;
                        switch(selection)
                        {
                        case 0:
                            exitResult = true;
                            break;
                        default:
                            int rating = customer->getRating(books[selection-1]->getIsbn());
                            cout << rating << endl;
                            if(rating != -1)
                            {
                                cout << "You rated this book with a " << rating << endl;
                            }
                            else
                            {
                                cout << "What would you rate this book? (1-5)" << endl;
                                cin >> rating;
                                manager.rateBook(customer, books[selection - 1]->getIsbn(), rating);
                            }
                            break;
                        }

                        if(exitResult)
                            break;
                    }
                }
               // manager.rateBook(customer, isbn, rating); 
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
