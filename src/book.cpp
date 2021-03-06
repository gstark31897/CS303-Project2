#include "book.h"
#include <iostream>

using namespace std;

Book::Book()
{
    m_isbn= -1;
    m_description = "";
}

Book::Book(long isbn, string description)
{
    m_isbn = isbn;
    m_description = description;
}

istream& operator>>(istream& in, Book& book)
{
    // read a line from the csv file and grab the required values
    string temp = "";
    getline(in, temp);
    int position = temp.find(',');
    book.m_isbn = stol(temp.substr(0, position));
    book.m_description = temp.substr(position + 2, temp.length()); 
    return in;
}
