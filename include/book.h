#ifndef H_BOOK
#define H_BOOK

#include <iostream> 
#include <string>


class Book
{
private:
    long m_isbn;
    std::string m_description;

public:
    Book();
    Book(long isbn, std::string description);

    void setIsbn(long isbn) {m_isbn = isbn;}
    void setDescription(std::string des) {m_description = des;}
    
    long getIsbn() {return m_isbn;}
    std::string getDescription() {return m_description;}
    
    friend std::istream& operator>>(std::istream& in, Book& book);
};
    
#endif
