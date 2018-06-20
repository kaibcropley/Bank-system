//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <vector>
#include <string>
#include "subaccount.h"

class Account {
public:
	// Constructor
	Account(std::string firstName, std::string lastName, int accountID);

	// Destructor
	~Account();

	// Returns the full name of the account owner.
	std::string GetName() const;

	// Returns account ID
	int GetAccountID() const;

	// Takes in SubAccount number and amount then returns if successful ly
	// deposited
	bool Deposit(int subAccNum, int amount);

	// Takes in SubAccount number and amount then returns if successfully
	// withdrew
	bool Withdraw(int subAccNum, int amount);

	// Takes in both SubAccount numbers and amount then returns if successfully
	// transfers between accounts
	bool Transfer(int subAccNum, int amount, SubAccount *otherAcc);

	// Prints out history of this account
	void printHistory() const;

	// Prints out all current balances of this account
	void getBalances() const;

	// Return's sub account object
	SubAccount *getSubAccount(int subAccountNum);

	// Used to compare two accounts by account ID for binary tree
	bool operator>(const Account &other) const;

	// Used to compare two accounts by account ID for binary tree
	bool operator<(const Account &other) const;

	// Used to compare two accounts by account ID for binary tree
	bool operator==(const Account &other) const;

	// Used to compare account with an account ID
	bool operator>(const int &accID) const;

	// Used to compare account with an account ID
	bool operator<(const int &accID) const;

	// Used to compare account with an account ID
	bool operator==(const int &accID) const;

private:
	// Constants
	const static int MAX_NUM_OF_SUBACCOUNTS = 10;
	// Class data
	std::string name;
	int accountID;
	// Vector containing SubAccounts
	std::vector<SubAccount *> subAcc;

	// Creates SubAccounts within vector
	void createSubAccounts();

	// Returns sub accounts name based on index
	std::string getSubAccountName(int subAccNum) const;
};


#endif //ASS5_ACCOUNT_H
