//
// Created by Youssef on 20.12.18.
//

#ifndef BANKOOP_ACCOUNT_H
#define BANKOOP_ACCOUNT_H

#include <string>
#include <vector>
//#include "Transaction.h"

class Transaction;

using std::string;
using std::vector;

class Account{

private:
    static unsigned long long idCounter;
    unsigned long long id;
    string name;
    double credit;

    vector<Transaction*> outgoingTxs;
    vector<Transaction*> incomingTxs;

protected:
    double feesPerTx;

public:
    Account();
    Account(const string &, double, double);
    virtual ~Account();

    void deposit(double);
    double withdraw(double);
    void transfer(Account &, double);

    void addOutgoingTx(Transaction * tx);
    void addIncomingTx(Transaction * tx);

    virtual void display() const;

    string getName() const;
    unsigned long long getId() const;
    double getCredit() const;
};

#endif //BANKOOP_ACCOUNT_H
