#ifndef H_BOOK
#define H_BOOK

#include <iostream> 
#include <string>


class Book
{
private:
    int m_isbn;
    std::string m_description;

public:
    Book();
    Book(int isbn, std::string description);

    void setIsbn(int isbn) {m_isbn = isbn;}
    void setDescription(std::string des) {m_description = des;}
    
    int getIsbn() {return m_isbn;}
    std::string getDescription() {return m_description;}
    
    friend std::istream& operator>>(std::istream& in, Book& book);
};
    
#endif
