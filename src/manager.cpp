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
        Book *tempBook;
        try
        {   tempBook = new Book();
            booksFile >> *tempBook;
            m_books.push_back(tempBook);
        }
        catch (...)
        {
            delete tempBook;
        }
    }
    booksFile.close();

    ifstream customersFile("customers.txt");
    getline(customersFile, temp);
    while(!customersFile.eof())
    {
        Customer *tempCustomer;
        try
        {
            tempCustomer = new Customer();
            customersFile >> *tempCustomer;
            m_customers.push_back(tempCustomer);
        }
        catch (...)
        {
            delete tempCustomer;
        }
    }
    customersFile.close();

    ifstream ratingsFile("ratings.txt");
    getline(ratingsFile, temp);
    while(!ratingsFile.eof())
    {
        Rating *tempRating;
        try
        {
            tempRating = new Rating();
            ratingsFile >> *tempRating;
            m_ratings[tempRating->getId()].push_back(tempRating);
        }
        catch (...)
        {
            delete tempRating;
        }
    }
    ratingsFile.close();
}


Manager::~Manager()
{
    for(vector<Book*>::iterator it = m_books.begin(); it != m_books.end(); ++it)
    {
        delete *it;
    }

    for(vector<Customer*>::iterator it = m_customers.begin(); it != m_customers.end(); ++it)
    {
        delete *it;
    }
}