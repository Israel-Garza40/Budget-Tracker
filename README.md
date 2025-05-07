#The budgettracker.cpp program is a simple console-based budget tracking tool that lets users manage personal expenses using fixed categories like Food, #Rent, and Utilities. Users can add transactions, view spending totals, and save or load data from a file. The program ensures input validation and #organizes logic into clear, modular functions for ease of use.

#Key Functions:
#-addTransaction: Lets users add a transaction by selecting a category and entering an amount.
#-showTransactions: Displays all recorded transactions.
#-calculateTotal: Calculates total spending across all transactions.
#-calculateTotal (overloaded): Calculates total spending for a specific category.
#-saveToFile: Saves all transactions to a text file.
#-loadFromFile: Loads transactions from a file on startup.
#-getCategoryChoice: Displays a fixed list of categories and returns the user's selection.
