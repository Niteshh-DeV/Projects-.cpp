#include <iostream>
using namespace std;

// Function prototypes
void checkBalance(int balance);
void depositMoney(int &balance);
void withdrawMoney(int &balance);

int main() {
    int balance = 1000; // Initial balance
    int choice;

    cout << "Welcome to the ATM" << endl;

    do {
        // Display menu
        cout << "\n1. Check Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                depositMoney(balance);
                break;
            case 3:
                withdrawMoney(balance);
                break;
            case 4:
                cout << "Thank you for using the ATM!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}

// Function to check balance
void checkBalance(int balance) {
    cout << "Your balance is: " << balance << endl;
}

// Function to deposit money
void depositMoney(int &balance) {
    int amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    if (amount > 0) {
        balance += amount;
        cout << "New balance is: " << balance << endl;
    } else {
        cout << "Invalid amount! Please enter a positive number." << endl;
    }
}

// Function to withdraw money
void withdrawMoney(int &balance) {
    int amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (amount > 0) {
        if (amount <= balance) {
            balance -= amount;
            cout << "New balance is: " << balance << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    } else {
        cout << "Invalid amount! Please enter a positive number." << endl;
    }
}