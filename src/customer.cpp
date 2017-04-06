#include "customer.h"

#include <stdlib.h>

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
    for(map<string, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
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


void Customer::addRating(Rating *rating)
{
    m_ratings[rating->getBookId()] = rating;
}


int Customer::getRating(string bookId)
{
    map<string, Rating*>::iterator it = m_ratings.find(bookId);
    if(it == m_ratings.end())
        return -1;
    return it->second->getRating();
}


float Customer::getSimilarity(Customer *customer)
{
    float similarity = 0.0f;
    for(map<string, Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        int value = customer->getRating(it->first);
        if(value == -1)
            continue;
        similarity += ((float)abs(value - it->second->getRating()));
    }
    return similarity;
}

