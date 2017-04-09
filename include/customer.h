#ifndef H_CUSTOMER
#define H_CUSTOMER

#include "rating.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>


class Customer
{
private: 
    int m_id;
    std::string m_name;
    std::map<int, Rating*> m_ratings;

public:
    Customer();
    Customer(int id, std::string name);

    ~Customer();
    
    void addRating(Rating *rating);
    int getRating(int isbn);
    int countRatings() { return m_ratings.size(); };

    int getId() {return m_id;}
    std::string getName() {return m_name;}

    float getSimilarity(Customer *customer);
    std::vector<Rating*> getRatings();
    std::vector<Rating*> getRecomendations(std::vector<Rating*> ratings);

    friend std::istream& operator>>(std::istream& in, Customer& customer);
};

#endif
