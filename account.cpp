//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#include <iostream>
#include <vector>
#include "account.h"

// Constructor
Account::Account(std::string firstName, std::string lastName, int accountID) :
		name{firstName + ' ' + lastName}, accountID(accountID),
		subAcc(MAX_NUM_OF_SUBACCOUNTS) {
	createSubAccounts();
}

// Destructor
Account::~Account() {
	for (unsigned int i{0}; i < subAcc.size(); i++) {
		delete subAcc[i];
	}
}

// Private method to create the SubAccount objects
void Account::createSubAccounts() {
	for (unsigned int i{0}; i < subAcc.size(); i++) {
		std::string s = std::to_string(accountID) + std::to_string(i);
		subAcc[i] = new SubAccount(s);
	}
	subAcc[1]->setLinkedAccount(subAcc[0]);
	subAcc[0]->setLinkedAccount(subAcc[1]);
	subAcc[3]->setLinkedAccount(subAcc[2]);
	subAcc[2]->setLinkedAccount(subAcc[3]);
}

// Returns the full name of account owner
std::string Account::GetName() const {
	return name;
}

// Returns AccountID
int Account::GetAccountID() const {
	return accountID;
};

// Takes in SubAccount number and amount then returns if successfully
// deposited
bool Account::Deposit(int subAccNum, int amount) {
	if (subAccNum > 9) {
		return false;
	}
	return subAcc[subAccNum]->Deposit(amount);
}

// Takes in SubAccount number and amount then returns if successfully
// withdrew
bool Account::Withdraw(int subAccNum, int amount) {
	return subAcc[subAccNum]->Withdraw(amount);
}

// Takes in both SubAccount numbers and amount then returns if successfully
// transfers between accounts
bool Account::Transfer(int subAccNum, int amount, SubAccount *otherAcc) {
	return subAcc[subAccNum]->Transfer(amount, otherAcc);
}

// Private method to get the names of each the sub accounts
std::string Account::getSubAccountName(int subAccNum) const {
	switch (subAccNum) {
		case 0:
			return "Money market";
		case 1:
			return "Prime Money Market";
		case 2:
			return "Long-term bond";
		case 3:
			return "Short-term bond";
		case 4:
			return "500 index Fund";
		case 5:
			return "Capital value Fund";
		case 6:
			return "Growth Equity Fund";
		case 7:
			return "Growth index Fund";
		case 8:
			return "Value Fund";
		case 9:
			return "Value index Fund";
		default:
			return "Error subAccount not found";
	}
}

// Return's sub account object
SubAccount *Account::getSubAccount(int subAccountNum) {
	return subAcc[subAccountNum];
}

// Prints history to the console
void Account::printHistory() const {
	std::cout << name << " " << std::to_string(accountID) << std::endl;
	for (unsigned int i{0}; i < subAcc.size(); i++) {
		std::vector<std::string> subAccHistory = subAcc[i]->getHistory();
		std::cout << "\t" << getSubAccountName(i) << ": $" << subAcc[i]->getBalance() << std::endl;
		for (unsigned int j{0}; j < subAccHistory.size(); j++) {
			std::cout << "\t\t" << subAccHistory[j];
		}
	}
}

// Prints out balances of account to console
void Account::getBalances() const {
	std::cout << name << " " << std::to_string(accountID) << std::endl;
	for (unsigned int i{0}; i < subAcc.size(); i++) {
		std::vector<std::string> subAccHistory = subAcc[i]->getHistory();
		std::cout << "\t" << getSubAccountName(i) << ": $" << subAcc[i]->getBalance() << std::endl;
	}
}

// Used to compare two accounts by account ID for binary tree
bool Account::operator>(const Account &other) const {
	return accountID > other.accountID;
}

// Used to compare two accounts by account ID for binary tree
bool Account::operator<(const Account &other) const {
	return accountID < other.accountID;
}

// Used to compare two accounts by account ID for binary tree
bool Account::operator==(const Account &other) const {
	return accountID == other.accountID;
}

// Used to compare account to a given account ID
bool Account::operator>(const int &accID) const {
	return accountID > accID;
}

// Used to compare account with an account ID
bool Account::operator<(const int &accID) const {
	return accountID < accID;
}

// Used to compare account with an account ID
bool Account::operator==(const int &accID) const {
	return accountID == accID;
}

