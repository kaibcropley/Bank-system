//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#include <fstream>
#include <cassert>
#include "bank.h"

// Constructor
Bank::Bank() : accountIDs(0) {

}

// Destructor
Bank::~Bank() {
	accounts.Empty();
}

// Reads file and returns queue with instructions
std::queue<std::string> Bank::readFile(const std::string &fileName) {
	std::queue<std::string> instructions;

	std::ifstream input(fileName);
	assert(input);
	std::string line;

	while (std::getline(input, line)) {
		split(line, instructions);
	}
	return instructions;
}

// Splits a string by it's whitespace
void Bank::split(std::string &str, std::queue<std::string> &instructions) {
	std::string newString;
	for (unsigned int i{0}; i < str.size(); i++) {
		if (str[i] == ' ' || (str[i] == '\n' || str[i] == '\r')) {
			instructions.push(newString);
			newString = "";
		} else {
			newString += str[i];
		}
	}
	instructions.push(newString);
}

// Executes instructions from queue, returns true if successful
void Bank::execute(std::queue<std::string> &instructions) {
	while (!instructions.empty()) {
		std::string currentJob = instructions.front();
		instructions.pop();
		if (currentJob == "O") {
			open(instructions);
		} else if (currentJob == "D") {
			deposit(instructions);
		} else if (currentJob == "W") {
			withdraw(instructions);
		} else if (currentJob == "T") {
			transfer(instructions);
		} else if (currentJob == "H") {
			accountHistory(std::stoi(instructions.front()));
			instructions.pop();
		}
	}
	std::cout << "Done processing" << std::endl << std::endl;
	printBalances();
}

// Open an account using instructions from a queue
bool Bank::open(std::queue<std::string> &instructions) {
	std::string firstName = instructions.front();
	instructions.pop();
	std::string lastName = instructions.front();
	instructions.pop();
	int accountID = std::stoi(instructions.front());
	instructions.pop();

	Account *a;
	if (accounts.Retrieve(accountID, a)) {
		std::cout << "ERROR: Account(" << accountID
				  << ") already created." << std::endl;
		return false;
	}

	Account *newAccount = new Account(firstName, lastName, accountID);
	accountIDs.push_back(accountID);
	return accounts.Insert(newAccount);
}

// Deposit money into a account using instructions from a queue
bool Bank::deposit(std::queue<std::string> &instructions) {
	std::string ID = instructions.front();
	instructions.pop();
	int accountID = std::stoi(ID.substr(0, 4));
	int subAccount = std::stoi(ID.substr(4, 5));
	int amount = std::stoi(instructions.front());
	instructions.pop();

	Account *a;
	if (!accounts.Retrieve(accountID, a)) {
		std::cout << "ERROR: Account(" << accountID
				  << ") not found during deposit." << std::endl;
		return false;
	}
	return a->Deposit(subAccount, amount);
}

// Withdraw money from an account using instructions from a queue
bool Bank::withdraw(std::queue<std::string> &instructions) {
	std::string ID = instructions.front();
	instructions.pop();
	int accountID = std::stoi(ID.substr(0, 4));
	int subAccount = std::stoi(ID.substr(4, 5));
	int amount = std::stoi(instructions.front());
	instructions.pop();

	Account *a;
	if (!accounts.Retrieve(accountID, a)) {
		std::cout << "ERROR: Account(" << accountID
				  << ") not found during withdraw." << std::endl;
		return false;
	}
	return a->Withdraw(subAccount, amount);
}

// Transfer money from one account to another using
// instructions from a queue
bool Bank::transfer(std::queue<std::string> &instructions) {
	std::string ID = instructions.front();
	instructions.pop();
	int accountID = std::stoi(ID.substr(0, 4));
	int subAccount = std::stoi(ID.substr(4, 5));
	int amount = std::stoi(instructions.front());
	instructions.pop();
	std::string secID = instructions.front();
	instructions.pop();
	int secAccountID = std::stoi(secID.substr(0, 4));
	int secSubAccount = std::stoi(secID.substr(4, 5));

	Account *a;
	if (!accounts.Retrieve(accountID, a)) {
		std::cout << "ERROR: Account(" << accountID
				  << ") not found during transfer." << std::endl;
		return false;
	}
	Account *a2;
	if (!accounts.Retrieve(secAccountID, a2)) {
		std::cout << "ERROR: Account(" << secAccountID
				  << ") not found during transfer." << std::endl;
		return false;
	}

	return a->Transfer(subAccount, amount, a2->getSubAccount(secSubAccount));
}

// Print history of a specific account
bool Bank::accountHistory(int accountID) const {
	Account *a;
	if (!accounts.Retrieve(accountID, a)) {
		std::cout << "ERROR: Account(" << accountID
				  << ") not found." << std::endl;
		return false;
	}
	a->printHistory();

	return true;
}

void Bank::printBalances() {
	std::cout << "Account balances: " << std::endl;
	for (unsigned int i{0}; i < accountIDs.size(); i++) {
		Account *a;
		accounts.Retrieve(accountIDs[i], a);
		a->getBalances();
	}
}
