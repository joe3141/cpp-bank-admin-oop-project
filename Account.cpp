//
// Created by Youssef on 20.12.18.
//

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Account.h"
#include "Transaction.h"

using std::cout;
using std::endl;
using std::logic_error;
using std::invalid_argument;

unsigned long long Account::idCounter = 0ll;

Account::Account() {
    id = 1ll;
    name = "Youssef";
    credit = 3.141592654;
    feesPerTx = 0;
}

Account::Account(const string & name, double initialCredit, double feesPerTx): name(name),
credit(initialCredit), feesPerTx(feesPerTx) {
    id = idCounter++; // UUID would be more appropriate, but I wanted to show use of static members.

    if(std::any_of(name.begin(), name.end(), ::isdigit))
        throw invalid_argument("Name can't contain numeric characters!");
}

Account::~Account() = default;

void Account::deposit(double amount) {
    if(amount < 0)
        throw std::invalid_argument("Cannot deposit a negative value!");

    this->credit += amount;
}

double Account::withdraw(double amount) {
    if(amount < 0)
        throw invalid_argument("Cannot withdraw a negative value!");

    if (amount > this->credit)
        throw logic_error("Insufficient funds");

    this->credit -= amount;

    return this->credit;
}

void Account::transfer(Account & entity, double amount) { // Used exclusively in transactions
    if(&entity == this)
        throw logic_error("Attempting to transfer money to self!");

    withdraw(amount + (feesPerTx * amount)); // Would throw here if credit is insufficient.
    entity.deposit(amount);
}

void Account::addIncomingTx(Transaction * tx) {
//    incomingTxs.push_back(tx);
    incomingTxs.push_back(tx);
}

void Account::addOutgoingTx(Transaction * tx) {
    outgoingTxs.push_back(tx);
}

void Account::display() const {
    cout << "==============================================================================" << endl;
    cout << this->name << "'s account has the following credit: " << this->credit << " and is liable to pay "
    << this->feesPerTx*100 << " % of each transaction as an additional fee." << endl;
}

string Account::getName() const{
    return name;
}

unsigned long long Account::getId() const{
    return id;
}

double Account::getCredit() const {
    return credit;
}