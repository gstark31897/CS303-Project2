#include "customer.h"

#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;


Customer::Customer()
{
    m_id = 0;
    m_name = "";
}


Customer::Customer(int id, string name)
{
    m_id = id;
    m_name = name;
}


Customer::~Customer()
{
    // clean up the rating objects
    for(map<long, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        delete it->second;
    }
}


istream& operator>>(istream& in, Customer& customer)
{
    // read a line from the csv file and grab the respective values
    string temp = "";
    getline(in, temp);
    int position = temp.find(',');
    customer.m_id = stoi(temp.substr(0, position));
    customer.m_name = temp.substr(position + 2, temp.length());
    return in;
}


void Customer::addRating(Rating *rating, bool write)
{
    // add the rating to out internal map
    m_ratings[rating->getBookId()] = rating;
    // write it to file if need be
    if (write)
    {
        ofstream file("ratings.txt", fstream::in | fstream::out | fstream::app);
        file << *rating << flush;
        file.close();
    }
}


int Customer::getRating(long bookId)
{
    map<long, Rating*>::iterator it = m_ratings.find(bookId);
    if(it == m_ratings.end())
        return -1;
    return it->second->getRating();
}


float Customer::getSimilarity(Customer *customer)
{
    float similarity = 0.0f;
    for(map<long, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        int value = customer->getRating(it->first);
        if(value == -1)
            continue;
        similarity += ((float)abs(value - it->second->getRating()));
    }
    // add 1 so the most popular books overall will get suggested when there are no similar customers
    return similarity + 1;
}


bool sortByRating(Rating* lhs, Rating* rhs)
{
    // util method for sorting rating objects
    return lhs->getRating() < rhs->getRating();
}


vector<Rating*> Customer::getRatings()
{
    // return a list of ratings
    vector<Rating*> temp;
    for(map<long, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        temp.push_back(it->second);
    }
    return temp;
}


vector<Rating*> Customer::getRecomendations(vector<Rating*> ratings)
{
    // return a sorted list of ratings that are not in the provided vector
    vector<Rating*> temp;
    for(map<long, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        // check if the book has been rated yet
        bool alreadyRated = false;
        for(vector<Rating*>::iterator it2 = ratings.begin(); it2 != ratings.end(); ++it2)
        {
            if(it->second->getBookId() == (*it2)->getBookId())
            {
                alreadyRated = true;
                break;
            }
        }
        // return the book if it has not
        if(!alreadyRated)
        {
            temp.push_back(it->second);
        }
    }
    return temp;
}
