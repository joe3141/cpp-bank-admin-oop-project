#include <iostream>
#include <unordered_map>
#include <limits>
#include <map>
#include "Account.h"
#include "StudentAccount.h"
#include "StandardAccount.h"
#include "Transaction.h"

typedef unsigned long long ull;

using std::cout;
using std::cin;
using std::endl;

using std::exception;

using std::unordered_map;
using std::map;

unordered_map<ull, Account *> accounts;

void welcomeScreen(){
    cout << "Welcome to bank admin app!\n Here you can:\n1-Create an account\n2-Check info for an account\n"
    << "3-Deposit money for an account\n4-Withdraw money from an account\n5-Issue a transaction\n6-Search by name"
    << "\n7-Exit"
    << endl;
}

void createAccount(){
    string name;
    cout << "Please enter your name:" << endl;
    cin >> name;

    string in;
    cout << "Are you a student? y/n" << endl;
    cin >> in;
    bool correct_input = false;

    while (!correct_input) {
        if (in == "y") {
            string matriculationNumber;
            cout << "Please enter your matriculation number:" << endl;
            cin >> matriculationNumber;


            bool success = false;
            while (!success) {
                try {

                    auto sa = new StudentAccount(name, 0, matriculationNumber);
                    success = true;
                    correct_input = true;

                    cout << "Account created successfully, your id is: " << sa->getId() << endl;
                    accounts[sa->getId()] = sa;
                } catch (exception &exception) {
                    cout << "Invalid input name, please try again." << endl;
                }
            }
        } else if (in == "n") {
            string ssid;
            cout << "Please enter your social security number:" << endl;
            cin >> ssid;

            bool success = false;
            while (!success) {
                try {
                    auto sa = new StandardAccount(name, 0, 0.1, ssid);
                    success = true;
                    correct_input = true;

                    cout << "Account created successfully, your id is: " << sa->getId() << endl;
                    accounts[sa->getId()] = sa;
                } catch (exception &exception) {
                    cout << "Invalid input name, please try again." << endl;
                }
            }
        } else {
            cout << "Invalid input: " << in << "\nPlease either enter `y` or `n`" << endl;
            cin >> in;
        }
    }
}

Account * getAccount(bool verbose, const string & txRole){
    ull id;

    while (cout << "Please enter the id of the " << txRole << " account:" << endl && !(std::cin >> id)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }

    auto pin = accounts.find(id);

    if(pin == accounts.end()){
       cout << "Account not found." << endl;
        return nullptr;
    }else{
        if (verbose)
            pin->second->display();
        return pin->second;
    }
}

void changeBalance(bool deposit){
    Account * a = getAccount(false, "");
    double amount;

    string outMessage = deposit ? "deposit" : "withdraw";
    while (cout << "Please enter the amount you want to " << outMessage << endl && !(cin >> amount)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }

    bool success = false;
    while (!success) {
        try{
            if(deposit)
                a->deposit(amount);
            else
                a->withdraw(amount);
            success = true;
            cout << "Amount deposited successfully" << endl;
        }catch (exception& e){
            cout << "Invalid amount value!" << endl;
        }
    }
}

void issueTx(){
    Account * issuer = getAccount(false, "issuer");
    Account * issuee = getAccount(false, "issuee");

    string item;
    double cost;
    cout << "Please enter a description of the item:" << endl;
    cin >> item;

    cout << "Please enter the cost of this item:" << endl;
    cin >> cost;

    try {
        issuer->withdraw(cost);
        issuee->deposit(cost);
    }catch (exception& e){
        if(cost > issuer->getCredit()) { // User defined exceptions would have been a valid solution here as well
            cout << "Insufficient funds, transaction can't be completed" << endl;
            return;
        }else if(cost < 0){
            cout << "Invalid cost value. Transaction can't be created" << endl;
        }else{
            cout << "Invalid input" << endl;
        }
    }
    auto tx = new Transaction(item, cost, issuer, issuee);


    issuer->addOutgoingTx(tx);
    issuee->addIncomingTx(tx);

    cout << "Transaction issued successfully" << endl;
}

// Credits for this function goes to:
// Compute Levenshtein Distance
// Martin Ettl, 2012-10-05

size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2)
{
    const size_t m(s1.size());
    const size_t n(s2.size());

    if( m==0 ) return n;
    if( n==0 ) return m;

    size_t *costs = new size_t[n + 1];

    for( size_t k=0; k<=n; k++ ) costs[k] = k;

    size_t i = 0;
    for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
    {
        costs[0] = i+1;
        size_t corner = i;

        size_t j = 0;
        for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
        {
            size_t upper = costs[j+1];
            if( *it1 == *it2 )
            {
                costs[j+1] = corner;
            }
            else
            {
                size_t t(upper<corner?upper:corner);
                costs[j+1] = (costs[j]<t?costs[j]:t)+1;
            }

            corner = upper;
        }
    }

    size_t result = costs[n];
    delete [] costs;

    return result;
}


void search(){
    string query;
    cout << "Please enter the name of the account you want to search for:" << endl;
    cin >> query;

    map<int, Account*> idx;

    for(const auto& it: accounts){
        idx[uiLevenshteinDistance(query, it.second->getName())] = it.second;
    }

    cout << "Closest matches are: " << endl;
    int j = 0;

    for(auto it = idx.begin(); it != idx.end() && j < 5; ++it){
        cout << "name: " <<  it->second->getName() << " id: " << it->second->getId() << endl;
        ++j;
    }
}

int main() {
    bool exit = false;

    while(!exit) {
        welcomeScreen();

        int input;
        cin >> input;

        switch (input){
            case 1:
                createAccount();
                break;
            case 2:
                getAccount(true, "");
                break;
            case 3:
                changeBalance(true);
                break;
            case 4:
                changeBalance(false);
                break;
            case 5:
                issueTx();
                break;
            case 6:
                search();
                break;
            case 7:
                cout << "Goodbye!" << endl;
                exit = true;
                continue;
            default:
                cout << "Invalid input!" << endl;
        }

    }

    for(auto& it : accounts)
        delete it.second;

    accounts.clear();
    return 0;
}