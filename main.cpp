#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

string filename = "bank_data.txt";

class BankAccount {
public:
    int accountNumber;
    string name;
    double balance;

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        ofstream file(filename, ios::app);
        file << accountNumber << "," << name << "," << balance << endl;
        file.close();

        cout << "\nAccount Created Successfully!\n";
    }
};

bool accountExists(int accNo) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string accStr;

        getline(ss, accStr, ',');

        if (stoi(accStr) == accNo) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void displayAccounts() {
    ifstream file(filename);
    string line;

    cout << "\n===== ACCOUNT RECORDS =====\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string accNo, name, balance;

        getline(ss, accNo, ',');
        getline(ss, name, ',');
        getline(ss, balance, ',');

        cout << "Account No : " << accNo << endl;
        cout << "Name       : " << name << endl;
        cout << "Balance    : Rs." << balance << endl;
        cout << "--------------------------\n";
    }

    file.close();
}

void searchAccount() {
    int accNo;
    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file(filename);
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string acc, name, bal;

        getline(ss, acc, ',');
        getline(ss, name, ',');
        getline(ss, bal, ',');

        if (stoi(acc) == accNo) {
            cout << "\nAccount Found\n";
            cout << "Account No : " << acc << endl;
            cout << "Name       : " << name << endl;
            cout << "Balance    : Rs." << bal << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

void depositMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    ifstream file(filename);
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string acc, name, bal;

        getline(ss, acc, ',');
        getline(ss, name, ',');
        getline(ss, bal, ',');

        double balance = stod(bal);

        if (stoi(acc) == accNo) {
            balance += amount;
            found = true;
        }

        temp << acc << "," << name << "," << balance << endl;
    }

    file.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found)
        cout << "\nAmount Deposited Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

void withdrawMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    ifstream file(filename);
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string acc, name, bal;

        getline(ss, acc, ',');
        getline(ss, name, ',');
        getline(ss, bal, ',');

        double balance = stod(bal);

        if (stoi(acc) == accNo) {
            found = true;

            if (amount <= balance) {
                balance -= amount;
                cout << "\nWithdrawal Successful!\n";
            } else {
                cout << "\nInsufficient Balance!\n";
            }
        }

        temp << acc << "," << name << "," << balance << endl;
    }

    file.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found)
        cout << "\nAccount Not Found!\n";
}

void checkBalance() {
    int accNo;
    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file(filename);
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string acc, name, bal;

        getline(ss, acc, ',');
        getline(ss, name, ',');
        getline(ss, bal, ',');

        if (stoi(acc) == accNo) {
            cout << "\nCurrent Balance: Rs." << bal << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

int main() {
    int choice;
    BankAccount account;

    do {
        cout << "\n================================";
        cout << "\n   BANK MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Create Account";
        cout << "\n2. Display Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit Money";
        cout << "\n5. Withdraw Money";
        cout << "\n6. Check Balance";
        cout << "\n7. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            account.createAccount();
            break;
        case 2:
            displayAccounts();
            break;
        case 3:
            searchAccount();
            break;
        case 4:
            depositMoney();
            break;
        case 5:
            withdrawMoney();
            break;
        case 6:
            checkBalance();
            break;
        case 7:
            cout << "\nThank You!\n";
            break;
        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
