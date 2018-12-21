//
// Created by root on 20.12.18.
//

#ifndef BANKOOP_STANDARDACCOUNT_H
#define BANKOOP_STANDARDACCOUNT_H

#include "Account.h"

class StandardAccount: public Account{
private:
    string ssid;

public:
    StandardAccount();
    StandardAccount(const string &, double, double, const string &);
    ~StandardAccount();

    void display() const override;
};


#endif //BANKOOP_STANDARDACCOUNT_H
