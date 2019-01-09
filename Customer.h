//
//  Customer.h
//  Project 2
//  Created by Austin Diaz on 11/19/18.
//  Copyright © 2018 Austin Diaz. All rights reserved.
//The first line indicates the number of customers in the file. Each customer information includes SSN (four digit number), first name, last name, account number (four digit number), account type (1: checking, 2: saving), and current balance. So, the second line indicates that Tom Smith has a checking account with the balance $10.00. Tom’s SSN is 7777 and his account number is 1000. In the project, you can assume that the text file has always correct format (= correct data).
#include <string>
using namespace std;

#ifndef Customer_h
#define Customer_h


class Customer{
public:
    bool setAccount(int ssn, int acctNumber, int acctType, double balance, string firstName, string lastName);
    int getAccountNumber();
    string getFirstName();
    string getLastName();
    int getAcctType();
    int getSsn();
    void customerList();
    void accoutInfo();
    double getBalance();
    void setBalance(double newBalance);
    
private:
    int ssn;
    int acctNumber;
    int acctType;
    double balance;
    string firstName;
    string lastName;
};

#endif /* Customer_h */
