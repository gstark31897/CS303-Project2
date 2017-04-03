#ifndef H_BOOK
#define H_BOOK

#include <iostream> 
#include <string>

class Book
{
    private:
    std::string m_isbn;
    std::string m_description;
    //std::vector<Books> m_BookList;

    public:
    Book();
    Book(std::string isbn, std::string description);

    void setIsbn(std::string isbn) {m_isbn = isbn;}
    void setDescription(std::string des) {m_description = des;}
    
    std::string getIsbn() {return m_isbn;}
    std::string getDescription() {return m_description;}
    
    friend std::istream& operator>>(std::istream& in, Book& book);
};
    
#endif
