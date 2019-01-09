#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Customer.h"
#define FIXED_DOUBLE(x) std::fixed << std::setprecision(2) << (x)
using namespace std;

bool Customer::setAccount(int newSsn, int newAcctNumber, int newAcctType, double newBalance, string newFirstName, string newLastName){
    firstName = newFirstName;
    lastName = newLastName;
    ssn = newSsn;
    acctNumber = newAcctNumber;
    
    if(newAcctType == 1 || newAcctType == 2){
        acctType = newAcctType;
    }
    
    else{
        cerr << "Error: Incorrect account type." << endl;
        return false;
    }
    
    if(newBalance < 0.00){
        cerr << "Error: Balance cannot be negative;" << endl;
        return false;
    }
    
    else{
        balance = newBalance;
    }
    
    return true;
}

int Customer::getAccountNumber()
{
    return acctNumber;
}


string Customer::getFirstName(){
    return firstName;
}

string Customer::getLastName(){
    return lastName;
}

int Customer::getAcctType(){
    return acctType;
}

int Customer::getSsn(){
    return ssn;
}

void Customer::setBalance(double newBalance){
    balance = newBalance;
}

double Customer::getBalance(){
    return balance;
}

void Customer::customerList(){
    cout << "\tSSN: "<<getSsn() << endl << "\tName: " << getFirstName() << " " << getLastName() << endl;
}

void Customer::accoutInfo(){
    cout <<"\tName: " << getFirstName() << " " << getLastName() << endl;
    cout << "\tAccount Number: " << getAccountNumber() << endl;
    cout << "\tAccount Type: " << ((getAcctType() == 1) ? "Checking\n" : "Savings\n");
    cout << "\tBalance: $" << FIXED_DOUBLE(getBalance()) << endl;
}
