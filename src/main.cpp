#include "customer.h"
#include <iostream>

using namespace std;

int main()
{
    Customer customer;
    cout << "Enter info" << endl;
    
    cin >> customer;
    
    cout << customer.getID() << endl;
    cout << customer.getName() << endl;
    
    return 0;
    
}
