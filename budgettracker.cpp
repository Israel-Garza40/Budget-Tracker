#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// ---------------------------
// Constants and Structures
// ---------------------------
const int MAX_TRANSACTIONS = 100;
const int NUM_CATEGORIES = 5;

const string transactionTypes[NUM_CATEGORIES] = {
    "Food", "Rent", "Utilities", "Entertainment", "Other"
};

struct Transaction {
    string category;
    float amount;
};

// ---------------------------
// Function Declarations
// ---------------------------
void displayCategoryMenu();
int getCategoryChoice();
void addTransaction(Transaction[], int&);
void showTransactions(const Transaction[], int);
float calculateTotal(const Transaction[], int);
float calculateTotal(const Transaction[], int, const string&); // Overloaded
void saveToFile(const Transaction[], int, const string&);
void loadFromFile(Transaction[], int&, const string&);

// ---------------------------
// Function Definitions
// ---------------------------

void displayCategoryMenu() {
    cout << "\nSelect a transaction category:\n";
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        cout << i + 1 << ". " << transactionTypes[i] << endl;
    }
}

int getCategoryChoice() {
    int choice;
    while (true) {
        displayCategoryMenu();
        cout << "Enter your choice (1-" << NUM_CATEGORIES << "): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > NUM_CATEGORIES) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid selection. Try again.\n";
        } else {
            break;
        }
    }
    return choice - 1; // return index
}

void addTransaction(Transaction transactions[], int& count) {
    if (count >= MAX_TRANSACTIONS) {
        cout << "Transaction limit reached.\n";
        return;
    }

    float amount;
    int categoryIndex = getCategoryChoice();

    cout << "Enter amount: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount. Try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    transactions[count++] = {transactionTypes[categoryIndex], amount};
    cout << "Transaction added under category '" << transactionTypes[categoryIndex] << "'.\n";
}

void showTransactions(const Transaction transactions[], int count) {
    if (count == 0) {
        cout << "No transactions to show.\n";
        return;
    }

    cout << "\n--- Transactions ---\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << setw(15) << transactions[i].category
             << " - $" << fixed << setprecision(2) << transactions[i].amount << endl;
    }
}

float calculateTotal(const Transaction transactions[], int count) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += transactions[i].amount;
    }
    return total;
}

// Overloaded: Total by category
float calculateTotal(const Transaction transactions[], int count, const string& category) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        if (transactions[i].category == category) {
            total += transactions[i].amount;
        }
    }
    return total;
}

void saveToFile(const Transaction transactions[], int count, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error writing to file.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        outFile << transactions[i].category << " " << transactions[i].amount << endl;
    }
    outFile.close();
    cout << "Data saved to file.\n";
}

void loadFromFile(Transaction transactions[], int& count, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "File not found. Starting fresh.\n";
        return;
    }

    count = 0;
    while (inFile >> transactions[count].category >> transactions[count].amount) {
        if (++count >= MAX_TRANSACTIONS) break;
    }
    inFile.close();
    cout << "Data loaded from file.\n";
}

// ---------------------------
// Main Program
// ---------------------------
int main() {
    Transaction transactions[MAX_TRANSACTIONS];
    int count = 0;
    int choice;
    string filename = "transactions.txt";

    loadFromFile(transactions, count, filename);

    do {
        cout << "\n--- Budget Tracker Menu ---\n";
        cout << "1. Add transaction\n";
        cout << "2. View all transactions\n";
        cout << "3. View total spending\n";
        cout << "4. View total by category\n";
        cout << "5. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTransaction(transactions, count);
                break;
            case 2:
                showTransactions(transactions, count);
                break;
            case 3:
                cout << "Total spending: $" << fixed << setprecision(2) 
                     << calculateTotal(transactions, count) << endl;
                break;
            case 4: {
                int catIndex = getCategoryChoice();
                cout << "Total for '" << transactionTypes[catIndex] << "': $"
                     << fixed << setprecision(2)
                     << calculateTotal(transactions, count, transactionTypes[catIndex]) << endl;
                break;
            }
            case 5:
                saveToFile(transactions, count, filename);
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}