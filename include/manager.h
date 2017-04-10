#ifndef H_MANAGER
#define H_MANAGER

#include "book.h"
#include "customer.h"
#include "rating.h"

#include <vector>
#include <map>


class Manager
{
private:
    std::map<long, Book*> m_books;
    std::map<int, Customer*> m_customers;

    double getSimilarity(int userId1, int userId2);

public:
    Manager();
    ~Manager();

    Customer* getCustomer(int id);

    std::vector<Book*> getRecomendations(Customer *customer);
    void rateBook(Customer *customer, long isbn, int rating);

    Book *getBook(long isbn);
    std::vector<Book*> getBooksByIsbn(std::string query);
    std::vector<Book*> getBooksByDescription(std::string query);
};

#endif
