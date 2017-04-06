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
    std::map<int, Customer*> m_customers;

    double getSimilarity(int userId1, int userId2);

public:
    Manager();
    ~Manager();

    Customer* getCustomer(int id);

    std::vector<Book*> getRecomendations();
    void rateBook(int userId, std::string isbn);
};

#endif
