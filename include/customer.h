#ifndef H_CUSTOMER
#define H_CUSTOMER

#include "rating.h"

#include <iostream>
#include <string>
#include <map>


class Customer
{
private: 
    int m_id;
    std::string m_name;
    std::map<std::string, Rating*> m_ratings;

public:
    Customer();
    Customer(int id, std::string name);

    ~Customer();
    
    void addRating(Rating *rating);
    int getRating(std::string isbn);
    int countRatings() { return m_ratings.size(); };

    int getId() {return m_id;}
    std::string getName() {return m_name;}

    float getSimilarity(Customer *customer);

    friend std::istream& operator>>(std::istream& in, Customer& customer);
};

#endif
