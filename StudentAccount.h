//
// Created by Youssef on 20.12.18.
//

#ifndef BANKOOP_STUDENTACCOUNT_H
#define BANKOOP_STUDENTACCOUNT_H

#include "Account.h"

class StudentAccount : public Account{

private:
    string matriculationNumber;

public:
    StudentAccount();
    StudentAccount(const string &, double, const string &);
    ~StudentAccount();

    void display() const override;
};


#endif //BANKOOP_STUDENTACCOUNT_H
