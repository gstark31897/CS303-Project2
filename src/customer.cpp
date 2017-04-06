#include "customer.h"

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
    for(vector<Rating*>::iterator it = m_ratings.begin(); it != m_ratings.end(); ++it)
    {
        delete *it;
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
    m_ratings.push_back(rating);
}

