//
// Created by root on 20.12.18.
//


#include <iostream>
#include "Transaction.h"

using std::cout;
using std::endl;

Transaction::Transaction() {issuer = nullptr; issuee = nullptr;}

Transaction::Transaction(const string & item, double cost, const Account * issuer, const Account * issuee):
item(item), cost(cost), issuer(issuer), issuee(issuee) {}

Transaction::~Transaction() {
    delete issuer;
    delete issuee;
};

void Transaction::display() {
    cout << issuer->getName() << " issued a transaction to " << issuee->getName() << " for item: " << item
    << "and price: " << cost;
}