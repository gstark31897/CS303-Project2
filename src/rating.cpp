#include "rating.h"
#include <string>

using namespace std;

Rating::Rating()
{
    m_cId = 0;
    m_rating = 0;
    m_bookId = 0;
}

Rating::Rating(int id, int rating, int book)
{
    m_cId = id;
    m_rating = rating;
    m_bookId = book;
}

istream& operator>>(istream &in, Rating& rating)
{
    string temp = ""; 
    getline(in, temp);
    //find the spot of the first comma
    int position = temp.find(',');
    //save customer id
    rating.m_cId = stoi(temp.substr(0, position));
    //put rest of string in temp variable
    temp = temp.substr(position + 2, temp.length()); 
    //find spot of second comma
    position = temp.find(',');
    rating.m_rating = stoi(temp.substr(0, position)); 
    rating.m_bookId = stoi(temp.substr(position + 2, temp.length()));
    return in;
}


ostream& operator<<(ostream &out, const Rating &rating)
{
    out << rating.m_cId << ", " << rating.m_rating << ", " << rating.m_bookId << endl;
    return out;
}
