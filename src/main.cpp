#include "manager.h"
#include <iostream>

using namespace std;


void clearCin()
{
    // util function for clearing inpu
    cin.clear();
    cin.ignore(10000, '\n');
}


void searchMenu(Manager &manager, Customer *customer)
{
    // menu for searching for books
    while(true)
    {
query:
        // Print out the menu
        cout << "*****Book Search*****" << endl;
        cout << "By ISBN (1)" << endl;
        cout << "By Description (2)" << endl;
        cout << "Main Menu (3)" << endl;
        cout << "Select One (1-3): " << flush;

        // get selection
        int choice = -1;
        cin >> choice;
        clearCin();

        if(choice == 3)
            return;

        cout << "Enter Query: " << flush;
        string line;
        getline(cin, line);

        vector<Book*> books;
        switch(choice)
        {
        case 1:
            books = manager.getBooksByIsbn(line);
            break;
        case 2:
            books = manager.getBooksByDescription(line);
            break;
        default:
            cout << "Invalid Choice" << endl;
            continue;
        }

        // let the user do stuff with the results
        while(true)
        {
            // print out the search results
            cout << "*****Result*****" << endl;
            for(long i = 0; i < (long)books.size(); ++i)
            {
               cout << books[i]->getIsbn() << ':' << books[i]->getDescription() << " (" << i + 1 << ')' << endl;
            }
            cout << "New Query (0)" << endl;
            cout << "Select One (0-" << books.size() << "): " << flush;

            long selection = -1;
            cin >> selection;
            clearCin();

            switch(selection)
            {
            case 0:
                // go back to the main section of this menu
                goto query;
            default:
                // make sure the book is in range
                if(selection < 0 || selection > (long)books.size())
                {
                    cout << "Invalid Selection" << endl;
                    continue;
                }
                int rating = customer->getRating(books[selection-1]->getIsbn());
                if(rating != -1)
                {
                    // tell the user what they rated the book
                    cout << "You rated this book with a " << rating << endl;
                }
                else
                {
                    // let the user rate it if they haven't yet
                    cout << "What would you rate this book? (1-5)" << endl;
                    cin >> rating;
                    if(rating > 5 || rating < 1)
                    {
                        cout << "Invalid Rating" << endl;
                        continue;
                    }
                    manager.rateBook(customer, books[selection - 1]->getIsbn(), rating);
                }
                break;
            }
        }
    }
}


int main()
{
    Manager manager;
    Customer *customer;

    while(true)
    {
        // print out the main menu
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
                // get the customer object for the specified user
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
                // check the customer object then open the search menu
                if(customer == NULL)
                {
                    cout << "You must log in first" << endl;
                    break;
                }
                searchMenu(manager, customer);
            }
            break;
        case 3:
            {
                // check the customer object then show the recomendations
                if(customer == NULL)
                {
                    cout << "You must log in first" << endl;
                    break;
                }
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
