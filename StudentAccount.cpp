//
// Created by Youssef on 20.12.18.
//

#include <iostream>
#include "StudentAccount.h"

using std::cout;
using std::endl;

StudentAccount::StudentAccount(): Account() {
    matriculationNumber = "03712740";
}
StudentAccount::StudentAccount(const string & name, double initialCredit, const string &
matriculationNumber)
: Account(name, initialCredit, 0), matriculationNumber(matriculationNumber) {}

StudentAccount::~StudentAccount() {}

void StudentAccount::display() const {
    Account::display();
    cout << getName() << " is a student, with the following matriculation number: " << this->matriculationNumber
    << endl;
    cout << "==============================================================================" << endl;
}