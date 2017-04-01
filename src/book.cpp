#include "book.h"
#include <iostream>

using namespace std;

Book::Book()
{
    m_isbn= "";
    m_description = "";
}

Book::Book(string isbn, string description)
{
    m_isbn = isbn;
    m_description = description;
}

istream& operator>>(istream& in, Book& book)
{
    string temp = "";
    getline(in, temp);
    int position = temp.find(',');
    book.m_isbn = temp.substr(0, position);
    book.m_description = temp.substr(position + 2, temp.length()); 
    return in;
}
