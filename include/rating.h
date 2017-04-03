#ifndef H_RATING
#define H_RATING

#include <iostream>

class Rating
{
    private:
    int m_cId;
    int m_rating; 
    std::string m_bookId;
    
    public:
    Rating();
    Rating(int id, int rating, std::string book);
    
    void setId(int id) {m_cId = id;}
    void setRating(int rating) {m_rating = rating;}
    void setBookId(std::string bookId) {m_bookId = bookId;}
    
    int getId() {return m_cId;}
    int getRating() {return m_rating;}
    std::string getBookId() {return m_bookId;}
    
    friend std::istream& operator>>(std::istream& in, Rating& rating);
};

#endif
