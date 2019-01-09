#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Customer.h"
#define FIXED_DOUBLE(x) std::fixed << std::setprecision(2) << (x)

using namespace std;

const int MAX_SIZE = 40;
int count1 = 0;
int checking = 0;
int saving = 0;

string getFileName();
bool openFile(ifstream& file, string fileName);
void printOptions();
void readFile(ifstream& file, string fileName, Customer *act_ptr[MAX_SIZE], int size);
void printCustomerList(Customer *act_ptr[MAX_SIZE]);
void deleteAccount(Customer *act_ptr[MAX_SIZE]);
void findCustomer(Customer *act_ptr[MAX_SIZE]);
void bankInfo(Customer *act_ptr[MAX_SIZE]);
double totalBalance(Customer *act_ptr[MAX_SIZE]);
void transferMoney(Customer *act_ptr[MAX_SIZE]);

int main(){
    Customer *act_ptr[MAX_SIZE];
    
    for(int i = 0; i<MAX_SIZE; i++){
        act_ptr[i] = nullptr;
    }
    
    ifstream file;
    string fileName;
    int option;
    
    printOptions();
    
    cin >> option;
    
    while(option != 7){
        
        if(option == 1){
            fileName = getFileName();
            
            if(openFile(file, fileName)){
                readFile(file, fileName, act_ptr, MAX_SIZE);
            }
            printOptions();
            cin >> option;
        }
        
        else if(option == 2){
            deleteAccount(act_ptr);
            printOptions();
            cin >> option;
        }
        
        else if(option == 3){
            findCustomer(act_ptr);
            printOptions();
            cin >> option;
        }
        
        else if(option == 4){
            bankInfo(act_ptr);
            printOptions();
            cin >> option;
        }
        
        else if(option == 5){
            transferMoney(act_ptr);
            printOptions();
            cin >> option;
        }
        
        else if(option == 6){
            printCustomerList(act_ptr);
            printOptions();
            cin >> option;
        }
        
        else if(option == 7){
            cout << "BYE!" << endl;
            break;
        }
        
        else if(option > 7){
            printOptions();
            cin >> option;
        }
    }
    cout << "Bye" << endl;
    return 0;
}

void printOptions(){
    cout << "Select your choice: " << endl;
    cout << "\t1. Read customer data file.\n";
    cout << "\t2. Close an account\n";
    cout << "\t3. Customer Info\n";
    cout << "\t4. Bank Info\n";
    cout << "\t5. Transfer Money\n";
    cout << "\t6. Customer List\n";
    cout << "\t7. Exit" <<endl;
}

string getFileName(){
    string fileName;
    
    cout<<"Enter file name: ";
    cin >> fileName;
    
    return fileName;
}

bool openFile(ifstream& file, string fileName){
    int limitOfTries = 0;
    file.open(fileName.c_str());
    
    if(!file.is_open() && limitOfTries != 10){
        cerr << "The File failed to open." << endl;
        cerr << "Check the FileName entered." << endl;
        
        fileName = getFileName();
        openFile(file, fileName);
        
        limitOfTries++;
        if(limitOfTries == 10){
            return false;
        }
    }
    return true;
}

void readFile(ifstream& file, string fileName, Customer *act_ptr[MAX_SIZE], int size){
    
    int ssn;
    int acctNumber;
    int acctType;
    double balance;
    string firstName;
    string lastName;
    int newAmount;
    int index;
    
    cout << "Read data..." <<endl;
    
    file >> newAmount;
    //while(!file.eof()
    for(int l = 0; l< newAmount; l++){
        if(count1 == MAX_SIZE){
            cerr << "There isn't enough room for more customers." << endl;
            break;
        }
        
        index = -1;
        
        for(int i = 0; i < MAX_SIZE; i++){
            if(!act_ptr[i]){
                index = i;
                break;
            }
        }
        
        if(index == -1){
            cerr << "ERROR: The account list is full." << endl;
            return;
        }
        
        ssn = 0;
        acctNumber = 0;
        acctType = 0;
        balance = 0;
        
        
        file >> ssn >> firstName >> lastName >> acctNumber >> acctType >> balance;
        if(acctType == 1 && checking == 20){
            cerr << "ERROR: max amount of checking accounts.\n Skipping Customer..."<< endl;
            continue;
        }
        else if(acctType == 2 && saving == 20){
            cerr << "ERROR: max amount of savings accounts.\n Skipping Customer..."<< endl;
            continue;
        }
        
        for(int j = 0; j < MAX_SIZE; j++){
            
            if(act_ptr[j]){
                if(act_ptr[j]->getAccountNumber() == acctNumber){
                    cerr << "Account Creation Failed – Account number " << acctNumber << " already exists." << endl;
                    break;
                }
                
                else if(act_ptr[j]->getSsn() == ssn && act_ptr[j]-> getFirstName() != firstName && act_ptr[j]-> getLastName() != lastName){
                    cerr << "Account Creation Failed – A customer with SSN " << ssn << " already exists." <<endl;
                    break;
                }
                
                else if(act_ptr[j]->getSsn() == ssn && act_ptr[j]-> getAcctType() == acctType){
                    cerr << "Account Creation Failed – " << act_ptr[j]->getFirstName() << " " << act_ptr[j]->getLastName() << " cannot have two"<<  (act_ptr[j]->getAcctType() == 1 ?  " checking accounts." : " savings account") <<endl;
                    break;
                }
            }
            
            else{
                act_ptr[index] = new Customer();
                act_ptr[index]->setAccount(ssn, acctNumber, acctType, balance, firstName, lastName);
                count1++;
                if(acctType == 1){
                    checking++;
                }
                else{
                    saving++;
                }
                break;
            }
        }
        
        
    }
    
    cout << "Done." << endl << endl << endl;
    file.close();
    
}

void printCustomerList(Customer *act_ptr[MAX_SIZE]){
    cout << count1<<endl;
    int index1 = 0;
    int *ssnArray = new int[count1];
    for(int i = 0; i < MAX_SIZE; i++){
        if(act_ptr[i]){
            ssnArray[index1] = act_ptr[i]->getSsn();
            index1++;
        }
    }
    
    for(int j = 0; j < count1; j++){
        for(int l = 1; l < count1; l++){
            if( ssnArray[l-1] > ssnArray[l]){
                swap(ssnArray[l-1], ssnArray[l]);
            }
        }
    }
    
    cout << "========== Customer List ==========" << endl;
    for(int i = 0; i < count1; i++){
        for(int k = 0; k < MAX_SIZE; k++){
            if(act_ptr[k] && act_ptr[k]->getSsn() == ssnArray[i]){
                act_ptr[k]->customerList();
            
                if( i != count1-1){
                    cout << endl;
                }
            break;
            }
        }
    }
    cout << "===================================" << endl;
    delete [] ssnArray;
}

void deleteAccount(Customer *act_ptr[MAX_SIZE]){
    int ssn;
    int count = 0;
    int acctNumber;
    
    cout << "Enter account number: ";
    cin >> acctNumber;
    
    
    for(int i = 0; i < MAX_SIZE; i++){
        if(act_ptr[i]){
            if(act_ptr[i]->getAccountNumber() == acctNumber){
                cout << "Enter Customers SSN: ";
                cin >> ssn;
                
                if(act_ptr[i]-> getSsn() == ssn){
                    cout << "\nAccount Closed." << endl;
                    act_ptr[i]->accoutInfo();
                    cout<< endl;
                    delete act_ptr[i];
                    act_ptr[i] = nullptr;
                    count1--;
                    if(act_ptr[i]->getAcctType() == 1){
                        checking--;
                    }
                    else{
                        saving--;
                    }
                    count++;
                        return;
                }
                
                else{
                    cout << "Incorrect SSN." << endl;
                    return;
                }
            }
        }
    }
        cout << "Incorrect Account Number." << endl << endl << endl;
}

void findCustomer(Customer *act_ptr[MAX_SIZE]){
    int searchMethod;
    
    cout<< "SSN(1)/Last Name(2)/Account Number(3): ";
    cin >> searchMethod;
    
    bool There = false;
    
    if(searchMethod == 1) {
        int ssn;
        cout << "Enter SSN: ";
        cin >> ssn;
        for(int i = 0; i < MAX_SIZE; i++){
            if(act_ptr[i]){
                if(act_ptr[i]->getSsn() == ssn){
                    act_ptr[i]->accoutInfo();
                    cout << endl << endl;
                    There = true;
                }
            }
        }
        if(!There){
        cout << "No customer with the SSN." << endl << endl;
        }
    }
    
    if(searchMethod == 2) {
        string lastName;
        cout << "Enter Last Name: ";
        cin >> lastName;
        for(int i = 0; i < MAX_SIZE; i++){
            if(act_ptr[i]){
                if(act_ptr[i]->getLastName() == lastName){
                    act_ptr[i]->accoutInfo();
                    cout << endl << endl;
                    There = true;
                }
            }
        }
        if(!There){
        cout << "No customer with the last name." << endl << endl;
        }
    }
    
    if(searchMethod == 3) {
        int acctNumber;
        cout << "Enter Account Numnber: ";
        cin >> acctNumber;
        for(int i = 0; i < MAX_SIZE; i++){
            if(act_ptr[i]){
                if(act_ptr[i]->getAccountNumber() == acctNumber){
                    act_ptr[i]->accoutInfo();
                    cout << endl << endl;
                    There = true;
                }
            }
        }
        
        if(!There){
        cout << "No customer with the account Number." << endl << endl;
        }
    }
    if(searchMethod > 3){
        findCustomer(act_ptr);
    }
    
}

void bankInfo(Customer *act_ptr[MAX_SIZE]){
    int index = 0;
    
    cout << "Number of Accounts: " << count1 << endl;
    int* actNumArr = new int[MAX_SIZE];
    
    for(int q = 0; q < MAX_SIZE/2; q++){
        actNumArr[q] = 0;
    }
    
    for(int h = 0; h< MAX_SIZE; h++){
        if(act_ptr[h] && act_ptr[h]->getAcctType() == 1){
            actNumArr[index] = act_ptr[h]->getAccountNumber();
            index++;
        }
    }
    
    for(int w = 0; w < index + 1; w++){
        for(int e = 1; e < index + 1; e++){
            if(actNumArr[e-1] > actNumArr[e]){
                swap(actNumArr[e-1],actNumArr[e]);
            }
        }
    }
    
    for(int y = 0; y<index + 1; y++){
        for(int r = 0; r < MAX_SIZE; r++){
            if(act_ptr[r]){
                if(act_ptr[r]->getAccountNumber() == actNumArr[y]){
                    double balance = act_ptr[r]->getBalance();
                    cout << "\t" << actNumArr[y] << ": $" << FIXED_DOUBLE(balance) << "(Checking)" << endl;
                }
            }
        }
    }
    
    delete [] actNumArr;
    
    index = 0;
    
    actNumArr = new int[MAX_SIZE];
    
    for(int q = 0; q < MAX_SIZE/2; q++){
        actNumArr[q] = 0;
    }
    
    for(int h = 0; h< MAX_SIZE; h++){
        if(act_ptr[h] && act_ptr[h]->getAcctType() == 2){
            actNumArr[index] = act_ptr[h]->getAccountNumber();
            index++;
        }
    }
    
    for(int w = 0; w < index + 1; w++){
        for(int e = 1; e < index + 1; e++){
            if(actNumArr[e-1] > actNumArr[e]){
                swap(actNumArr[e-1],actNumArr[e]);
            }
        }
    }
    for(int y = 0; y<index + 1; y++){
        for(int r = 0; r < MAX_SIZE; r++){
            if(act_ptr[r]){
                if(act_ptr[r]->getAccountNumber() == actNumArr[y]){
                    double balance = act_ptr[r]->getBalance();
                    cout<<  "\t"  << actNumArr[y] << ": $" << FIXED_DOUBLE(balance) << "(Savings)" << endl;
                }
            }
        }
    }
    
    delete [] actNumArr;
    
    cout<<endl;
    
    //Prints list of customers and there info for bank;
    
    int* array = new int[MAX_SIZE/2];
    
    for(int u = 0; u < MAX_SIZE/2; u++){
        array[u] = 0;
    }
    
    int *ssnArray = new int[count1];
    
    int index1 = 0;
    for(int kk = 0; kk < MAX_SIZE; kk++ ){
        if(act_ptr[kk]){
            ssnArray[index1] = act_ptr[kk]->getSsn();
            index1++;
        }
    }
    
    for(int nn = 0; nn < count1; nn++){
        for(int nn = 1; nn < count1; nn++){
            if(ssnArray[nn-1] > ssnArray[nn]){
                swap(ssnArray[nn-1],ssnArray[nn]);
            }
        }
    }
    
    int count2 = 1;
    for(int jj = 1; jj<count1; jj++){
        if(ssnArray[jj-1] != ssnArray[jj]){
            count2++;
        }
    }
    
    int l = 0;
    index1 = 0;
    
    cout << "Number of Customers: " << count2 << endl;
    for(int i = 0; i < MAX_SIZE; i++){
        
        bool bothTypes = false;
        bool used = false;
        
        int j = MAX_SIZE;
        
        if(act_ptr[i] && act_ptr[i]->getSsn() == ssnArray[index1]){
        index1++;
            
         int ssn = act_ptr[i]->getSsn();
            
            for(int k = 0; k< MAX_SIZE; k++){
                if(i == array[k] && array[k] != 0){
                    used = true;
                    break;
                }
            }
            
            if(used){
                continue;
            }
            
            while(i < j){
                if(act_ptr[j] &&  ssn == act_ptr[j]->getSsn()){
                    bothTypes = true;
                    array[l] = j;
                    l++;
                    break;
                }
                j--;
            }
        
            
            if(bothTypes){
                index1++;
                cout <<  "\t" << act_ptr[i]->getFirstName() << " " << act_ptr[i]->getLastName() << ": " << ssn << " - ";
                if( act_ptr[i]-> getAcctType() == 1){
                    cout << act_ptr[i]-> getAccountNumber() << "($" << act_ptr[i]-> getBalance() << "), ";
                    cout << act_ptr[j]->getAccountNumber() << "($" << act_ptr[j]-> getBalance() << ")" << endl;
                }
                else
                {
                    cout << act_ptr[j]-> getAccountNumber() << "($" << act_ptr[j]-> getBalance() << "), ";
                    cout << act_ptr[i]->getAccountNumber() << "($" << act_ptr[i]-> getBalance() << ")" << endl;
                }
            }
            else{
                cout <<  "\t" << act_ptr[i]->getFirstName() << " " << act_ptr[i]->getLastName() << ": " << ssn << " - " << act_ptr[i]-> getAccountNumber() << "($" << act_ptr[i]-> getBalance() << ")" << endl;
            }
            i = 0;
        }
    }
    
    delete[] array;
    cout << endl;
    //Print out total Balance
    cout <<  "\t" << "Total Balance: $" <<  FIXED_DOUBLE(totalBalance(act_ptr)) << endl << endl;
}

double totalBalance(Customer *act_ptr[MAX_SIZE]){
    double totalBalance = 0;
    
    for(int i = 0; i < MAX_SIZE; i++){
        if(act_ptr[i]){
            totalBalance += act_ptr[i]->getBalance();
        }
    }
    
    return totalBalance;
}

void transferMoney(Customer *act_ptr[MAX_SIZE]){
    int sourceAccount;
    int destinationAccount;
    int sourceSsn;
    int destinationSsn;
    int sourceIndex;
    int destinationIndex;
    double transferAmount;
    
    bool sourceAccountExists = false;
    bool destinationAccountExists = false;
    
    cout << "Source Account: ";
    cin >> sourceAccount;
    
    cout << "Destination Account: ";
    cin >> destinationAccount;
    
    cout << "Money Account: ";
    cin >> transferAmount;
    
    for(int i = 0; i < MAX_SIZE; i++){
        if(act_ptr[i]){
            if(act_ptr[i]->getAccountNumber() == sourceAccount){
                sourceAccountExists = true;
                sourceSsn = act_ptr[i]-> getSsn();
                sourceIndex = i;
                break;
            }
        }
    }
    if(!sourceAccountExists){
        cout << "Transfer Fail – Incorrect account number" << endl << endl;
        return;
    }
    
    for(int i = 0; i < MAX_SIZE; i++){
        if(act_ptr[i]){
            if(act_ptr[i]->getAccountNumber() == destinationAccount){
                destinationAccountExists = true;
                destinationSsn = act_ptr[i]-> getSsn();
                destinationIndex = i;
                break;
            }
        }
    }
    
    if(!destinationAccountExists){
        cout << "Transfer Fail – Incorrect account number" << endl << endl;
        return;
    }
    
    if(sourceSsn == destinationSsn){
        if(act_ptr[sourceIndex]->getBalance() < transferAmount){
            cerr << "Transfer Fail – Insufficient amount." << endl << endl;
            return;
        }
        else{
            double newBalance = act_ptr[sourceIndex]-> getBalance() - transferAmount;
            act_ptr[sourceIndex]-> setBalance(newBalance);
            newBalance = act_ptr[destinationIndex]->getBalance() + transferAmount;
            act_ptr[destinationIndex]->setBalance(newBalance);
            
            cout << "Transfer Succeed." << endl << endl;
        }
    }
    
    else{
        if(act_ptr[sourceIndex]->getBalance() < transferAmount + 5.00){
            cerr << "Transfer Fail – Insufficient amount." << endl <<endl;
            return;
        }
        else{
            double newBalance = act_ptr[sourceIndex]-> getBalance() - transferAmount - 5.00;
            act_ptr[sourceIndex]-> setBalance(newBalance);
            newBalance = act_ptr[destinationIndex]->getBalance() + transferAmount;
            act_ptr[destinationIndex]->setBalance(newBalance);
            cout << "Transfer Succeed." << endl << endl;
        }
    }
    
    cout << "New Balance" << endl;
    
    if(act_ptr[sourceIndex]->getAccountNumber() < act_ptr[destinationIndex]->getAccountNumber()){
    cout << "\t" << act_ptr[sourceIndex]->getAccountNumber() << ": " << "$" << FIXED_DOUBLE(act_ptr[sourceIndex]->getBalance()) << endl;
    cout << "\t" << act_ptr[destinationIndex]->getAccountNumber() << ": " << "$" << FIXED_DOUBLE(act_ptr[destinationIndex]->getBalance()) << endl << endl;
    }
    else{
        cout << "\t" << act_ptr[destinationIndex]->getAccountNumber() << ": " << "$" << FIXED_DOUBLE(act_ptr[destinationIndex]->getBalance()) << endl;
        cout << "\t" << act_ptr[sourceIndex]->getAccountNumber() << ": " << "$" << FIXED_DOUBLE(act_ptr[sourceIndex]->getBalance()) << endl << endl;
    }
    
}
