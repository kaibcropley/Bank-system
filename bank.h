//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#ifndef ASS5_BANK_H
#define ASS5_BANK_H


#include <string>
#include <queue>
#include "bstree.h"

class Bank {
public:
	// Constructor
	Bank();

	// Destructor
	~Bank();

	// Reads file and returns queue with instructions
	std::queue<std::string> readFile(const std::string &fileName);

	// Executes instructions from queue, returns true if successful
	void execute(std::queue<std::string> &instructions);

private:
	// Open an account using instructions from a queue
	bool open(std::queue<std::string> &instructions);

	// Deposit money into a account using instructions from a queue
	bool deposit(std::queue<std::string> &instructions);

	// Withdraw money from an account using instructions from a queue
	bool withdraw(std::queue<std::string> &instructions);

	// Transfer money from one account to another using
	// instructions from a queue
	bool transfer(std::queue<std::string> &instructions);

	// Print history of a specific account
	bool accountHistory(int accountID) const;

	// Banks data
	BSTree accounts;
	std::vector<int> accountIDs;

	// Splits a string by it's whitespace
	void split(std::string &str, std::queue<std::string> &instructions);

	// Prints all balances of all accounts
	void printBalances();
};


#endif //ASS5_BANK_H
