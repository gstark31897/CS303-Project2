#ifndef H_CUSTOMER
#define H_CUSTOMER

#include "rating.h"

#include <iostream>
#include <string>
#include <vector>


class Customer
{
private: 
    int m_id;
    std::string m_name;
    std::vector<Rating*> m_ratings;

public:
    Customer();
    Customer(int id, std::string name);

    ~Customer();
    
    void addRating(Rating *rating);

    int getId() {return m_id;}
    std::string getName() {return m_name;}

    friend std::istream& operator>>(std::istream& in, Customer& customer);
};

#endif
