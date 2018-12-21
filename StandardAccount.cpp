//
// Created by root on 20.12.18.
//

#include <iostream>
#include "StandardAccount.h"

using std::cout;
using std::endl;

StandardAccount::StandardAccount(): Account() {ssid = "DEADBEEF";}
StandardAccount::StandardAccount(const string & name,
        double initialCredit, double feesPerTx, const string & ssid):
        Account(name, initialCredit, feesPerTx) {
    this->ssid = ssid;
}
StandardAccount::~StandardAccount() {}

void StandardAccount::display() const {
    Account::display();
    cout << getName() << "'s social security number is: " << this->ssid << endl;
    cout << "==============================================================================" << endl;
}