#include "manager.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;


Manager::Manager()
{
    // string used to remove the first line from each file
    string temp;

    // read the book objects from the file
    ifstream booksFile("books.txt");
    getline(booksFile, temp);
    while(!booksFile.eof())
    {
        Book *tempBook;
        try
        {
            // save the book in a map keyed by the book's isbn
            tempBook = new Book();
            booksFile >> *tempBook;
            m_books[tempBook->getIsbn()] = tempBook;
        }
        catch (...)
        {
            delete tempBook;
        }
    }
    booksFile.close();

    // read the customer objects from the file
    ifstream customersFile("customers.txt");
    getline(customersFile, temp);
    while(!customersFile.eof())
    {
        Customer *tempCustomer;
        try
        {
            // save the book in a map keyed by the user's id
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

    // read the rating objects
    ifstream ratingsFile("ratings.txt");
    getline(ratingsFile, temp);
    while(!ratingsFile.eof())
    {
        Rating *tempRating;
        try
        {
            // save the rating in the user it belongs to
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
    // clean up all the book objects
    for(map<long, Book*>::iterator it = m_books.begin(); it != m_books.end(); ++it)
    {
        delete it->second;
    }

    // clean up all the customer objects (ratings are cleaned by the customer deconstructor)
    for(map<int, Customer*>::iterator it = m_customers.begin(); it != m_customers.end(); ++it)
    {
        delete it->second;
    }
}


Customer* Manager::getCustomer(int id)
{
    // return the requested customer (or NULL)
    map<int, Customer*>::iterator it = m_customers.find(id);
    if(it == m_customers.end())
        return NULL;
    return it->second;
}


bool compairWeightedValue(pair<int, double> lhs, pair<int, double> rhs)
{
    // utility used by the sort function
    return lhs.second < rhs.second;
}


void getRecomendationsThread(Customer *customer, Customer *customer2, vector<Rating*> &customerRatings, map<int, float> &weights, map<int, vector<Rating*>> &ratings, mutex &mapLock)
{
    // method used for recomendation processing thread
    // get the values that we want
    float weight = customer2->getSimilarity(customer);
    vector<Rating*> recomendations = customer2->getRecomendations(customerRatings);
    // lock the mutex and modify the maps
    mapLock.lock();
    weights[customer2->getId()] = weight;
    ratings[customer2->getId()] = recomendations;
    mapLock.unlock();
}


vector<Book*> Manager::getRecomendations(Customer *customer)
{
    vector<Book*> output;
    map<int, float> weights;
    map<int, vector<Rating*>> ratings;
    map<long, float> weightedRatings;
    mutex mapLock;
    vector<thread> processingThreads;
    vector<Rating*> customerRatings = customer->getRatings();
    // spawn all the threads for processing the recomendations
    for(map<int, Customer*>::iterator it = m_customers.begin(); it != m_customers.end(); ++it)
    {
        if(it->second == customer)
            continue;
        thread t(getRecomendationsThread, customer, it->second, ref(customerRatings), ref(weights), ref(ratings), ref(mapLock));
        processingThreads.push_back(move(t));
    }
    // join all the threads before we continue
    for(vector<thread>::iterator it = processingThreads.begin(); it != processingThreads.end(); ++it)
    {
        it->join();
    }
    // check if we have any similar users
    bool hasSimilar = false;
    for(map<int, float>::iterator it = weights.begin(); it != weights.end(); ++it)
    {
       if(it->second > 0.0)
       {
           hasSimilar = true;
           break;
       }
    }
    // calculate the weight for suggesting books
    for(map<int, float>::iterator it = weights.begin(); it != weights.end(); ++it)
    {
        for(vector<Rating*>::iterator it2 = ratings[it->first].begin(); it2 != ratings[it->first].end(); ++it2)
        {
            if(weightedRatings.find((*it2)->getBookId()) == weightedRatings.end())
                weightedRatings[(*it2)->getBookId()] = 0.0;
            // add the weighted rating if we have similar users, unweighted rating if we don't have similar users
            if(hasSimilar)
                weightedRatings[(*it2)->getBookId()] += it->second * (*it2)->getRating();
            else
                weightedRatings[(*it2)->getBookId()] += (*it2)->getRating();
        }
    }
    // make a vector of pairs that we can sort
    vector<pair<long, float>> bookRatings;
    for(map<long, float>::iterator it = weightedRatings.begin(); it != weightedRatings.end(); ++it)
    {
        bookRatings.push_back(*it);
    }
    // sort the vector
    sort(bookRatings.begin(), bookRatings.end(), compairWeightedValue);
    // get the book objects, exit after we get the top 10
    for(vector<pair<long, float>>::iterator it = bookRatings.begin(); it != bookRatings.end(); ++it)
    {
        output.push_back(getBook(it->first));
        if(output.size() == 10)
            break;
    }
    return output;
}


Book* Manager::getBook(long isbn)
{
    // return the requested book (or NULL)
    map<long, Book*>::iterator it = m_books.find(isbn);
    if(it != m_books.end())
        return it->second;
    return NULL;
}


void Manager::rateBook(Customer *customer, long isbn, int rating)
{
    // create a new rating and have it written to file
    customer->addRating(new Rating(customer->getId(), rating, isbn), true);
}


vector<Book*> Manager::getBooksByIsbn(string query)
{
    // search for books by isbn
    vector<Book*> output;
    for(map<long, Book*>::iterator it = m_books.begin(); it != m_books.end(); ++it)
    {
        // cast the isbn to a string and add it to the return value if it contains our query string
        if(to_string(it->first).find(query) != string::npos)
            output.push_back(getBook(it->first));
    }
    return output;
}


vector<Book*> Manager::getBooksByDescription(string query)
{
    // search for books by description
    vector<Book*> output;
    for(map<long, Book*>::iterator it = m_books.begin(); it != m_books.end(); ++it)
    {
        // add the book to the return value if its description contains our query
        if(string(it->second->getDescription()).find(query) != string::npos)
            output.push_back(getBook(it->first));
    }
    return output;
}
