#include "manager.h"

#include <fstream>
#include <iostream>
#include <algorithm>

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
            m_books[tempBook->getIsbn()] = tempBook;
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
    for(map<long, Book*>::iterator it = m_books.begin(); it != m_books.end(); ++it)
    {
        delete it->second;
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


bool compairWeightedValue(pair<int, double> lhs, pair<int, double> rhs)
{
    return lhs.second < rhs.second;
}


vector<Book*> Manager::getRecomendations(Customer *customer)
{
    vector<Book*> output;
    map<int, float> weights;
    map<int, vector<Rating*>> ratings;
    map<long, float> weightedRatings;
    vector<Rating*> customerRatings = customer->getRatings();
    for(map<int, Customer*>::iterator it = m_customers.begin(); it != m_customers.end(); ++it)
    {
        if(it->second == customer)
            continue;
        weights[it->first] = it->second->getSimilarity(customer);
        ratings[it->first] = it->second->getRecomendations(customerRatings);
    }

    for(map<int, float>::iterator it = weights.begin(); it != weights.end(); ++it)
    {
        for(vector<Rating*>::iterator it2 = ratings[it->first].begin(); it2 != ratings[it->first].end(); ++it2)
        {
            if(weightedRatings.find((*it2)->getBookId()) == weightedRatings.end())
                weightedRatings[(*it2)->getBookId()] = 0.0;
            weightedRatings[(*it2)->getBookId()] += it->second * (*it2)->getRating();
        }
    }

    vector<pair<long, float>> bookRatings;
    for(map<long, float>::iterator it = weightedRatings.begin(); it != weightedRatings.end(); ++it)
    {
        bookRatings.push_back(*it);
    }
    sort(bookRatings.begin(), bookRatings.end(), compairWeightedValue);

    for(vector<pair<long, float>>::iterator it = bookRatings.begin(); it != bookRatings.end(); ++it)
    {
        output.push_back(getBook(it->first));
    }

    return output;
}


Book* Manager::getBook(long isbn)
{
    map<long, Book*>::iterator it = m_books.find(isbn);
    if(it != m_books.end())
        return it->second;
    return NULL;
}


void Manager::rateBook(Customer *customer, long isbn, int rating)
{
    customer->addRating(new Rating(customer->getId(), rating, isbn), true);
}

