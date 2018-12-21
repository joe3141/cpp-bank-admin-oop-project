//
// Created by root on 20.12.18.
//

#ifndef BANKOOP_TRANSACTION_H
#define BANKOOP_TRANSACTION_H

#include <string>
#include "Account.h"

using std::string;

class Transaction {
private:
    string item; // Description for an arbitrary item
    double cost;
    const Account * issuer;
    const Account * issuee;

public:
    Transaction();
    Transaction(const string &, double, const Account *, const Account *);
    ~Transaction();

    void display();
};


#endif //BANKOOP_TRANSACTION_H
