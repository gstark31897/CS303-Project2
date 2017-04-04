#include "manager.h"

#include <fstream>
#include <iostream>

using namespace std;


Manager::Manager()
{
    string temp;

    ifstream booksFile("books.txt");
    getline(booksFile, temp);
    while(!booksFile.eof())
    {
        try
        {
            Book tempBook;
            booksFile >> tempBook;
            m_books.push_back(tempBook);
        }
        catch (...) {}
    }
    booksFile.close();

    ifstream customersFile("customers.txt");
    getline(customersFile, temp);
    while(!customersFile.eof())
    {
        try
        {
            Customer tempCustomer;
            customersFile >> tempCustomer;
            m_customers.push_back(tempCustomer);
        }
        catch (...) {}
    }
    customersFile.close();

    ifstream ratingsFile("ratings.txt");
    getline(ratingsFile, temp);
    while(!ratingsFile.eof())
    {
        try
        {
            Rating tempRating;
            ratingsFile >> tempRating;
            m_ratings.push_back(tempRating);
        }
        catch (...) {}
    }
    ratingsFile.close();
}
