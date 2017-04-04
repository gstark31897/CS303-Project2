#ifndef H_CUSTOMER
#define H_CUSTOMER

#include <iostream>
#include <string>


class Customer
{
private: 
    int m_id;
    std::string m_name;

public:
    Customer();
    Customer(int nId, std::string nName);
    
    void setID(int nId) {m_id = nId;}
    void setName(std::string name) {m_name = name;}

    int getID() {return m_id;}
    std::string getName() {return m_name;}

    friend std::istream& operator>>(std::istream& in, Customer& customer);
};

#endif
