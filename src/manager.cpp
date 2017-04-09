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
            m_customers[tempCustomer->getId()] = tempCustomer;
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
            m_customers[tempRating->getId()]->addRating(tempRating);
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

    for(map<int, Customer*>::iterator it = m_customers.begin(); it != m_customers.end(); ++it)
    {
        delete it->second;
    }
}


Customer* Manager::getCustomer(int id)
{
    map<int, Customer*>::iterator it = m_customers.find(id);
    if(it == m_customers.end())
        return NULL;
    return it->second;
}

