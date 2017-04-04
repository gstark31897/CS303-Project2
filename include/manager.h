#ifndef H_USERMANAGER
#define H_USERMANAGER

#include "book.h"
#include "customer.h"
#include "rating.h"

#include <vector>


class Manager
{
private:
    std::vector<Book> m_books;
    std::vector<Customer> m_customers;
    std::vector<Rating> m_ratings;

public:
    Manager();
};

#endif
