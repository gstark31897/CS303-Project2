#ifndef H_USERMANAGER
#define H_USERMANAGER

#include "book.h"
#include "customer.h"
#include "rating.h"

#include <vector>
#include <map>


class Manager
{
private:
    std::vector<Book*> m_books;
    std::vector<Customer*> m_customers;
    std::map<int, std::vector<Rating*>> m_ratings;

    double getSimilarity(int userId1, int userId2);

public:
    Manager();
    ~Manager();

    std::vector<Book*> getRecomendations();
    void rateBook(int userId, std::string isbn);
};

#endif
