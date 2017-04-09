#ifndef H_RATING
#define H_RATING

#include <iostream>


class Rating
{
    private:
    int m_cId;
    int m_rating; 
    int m_bookId;
    
    public:
    Rating();
    Rating(int id, int rating, int book);
    
    void setId(int id) {m_cId = id;}
    void setRating(int rating) {m_rating = rating;}
    void setBookId(int bookId) {m_bookId = bookId;}
    
    int getId() {return m_cId;}
    int getRating() {return m_rating;}
    int getBookId() {return m_bookId;}

    bool operator<(Rating &rhs) { return getRating() < rhs.getRating(); };
    
    friend std::istream& operator>>(std::istream& in, Rating& rating);
    friend std::ostream& operator<<(std::ostream& out, const Rating& rating);
};

#endif
