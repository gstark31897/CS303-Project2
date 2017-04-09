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
    for(map<int, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        delete it->second;
    }
}


istream& operator>>(istream& in, Customer& customer)
{
    string temp = "";
    getline(in, temp);
    int position = temp.find(',');
    customer.m_id = stoi(temp.substr(0, position));
    customer.m_name = temp.substr(position + 2, temp.length());
    return in;
}


void Customer::addRating(Rating *rating, bool write)
{
    m_ratings[rating->getBookId()] = rating;

    if (write)
    {
        ofstream file("ratings.txt", fstream::in | fstream::out | fstream::app);
        file << *rating << flush;
        file.close();
    }
}


int Customer::getRating(int bookId)
{
    map<int, Rating*>::iterator it = m_ratings.find(bookId);
    if(it == m_ratings.end())
        return -1;
    return it->second->getRating();
}


float Customer::getSimilarity(Customer *customer)
{
    float similarity = 0.0f;
    for(map<int, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
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
    return lhs->getRating() < rhs->getRating();
}


vector<Rating*> Customer::getRatings()
{
    vector<Rating*> temp;
    for(map<int, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        temp.push_back(it->second);
    }
    sort(temp.begin(), temp.end(), sortByRating);
    return temp;
}


vector<Rating*> Customer::getRecomendations(vector<Rating*> ratings)
{
    vector<Rating*> temp;
    for(map<int, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        bool alreadyRated = false;
        for(vector<Rating*>::iterator it2 = ratings.begin(); it2 != ratings.end(); ++it2)
        {
            if(it->second->getBookId() == (*it2)->getBookId())
            {
                alreadyRated = true;
                break;
            }
        }

        if(!alreadyRated)
        {
            temp.push_back(it->second);
        }
    }
    sort(temp.begin(), temp.end(), sortByRating);
    return temp;
}
