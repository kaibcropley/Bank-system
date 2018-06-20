//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#ifndef ASS5_SUBACCOUNT_H
#define ASS5_SUBACCOUNT_H

#include <vector>
#include <string>

class SubAccount {
public:
	// Constructor
	explicit SubAccount(std::string accNum);

	// Takes in SubAccount number and amount then returns if successfully
	// deposited
	bool Deposit(int amount);

	// Takes in SubAccount number and amount then returns if successfully
	// withdrew
	bool Withdraw(int amount);

	// Takes in SubAccount number and amount then returns if successfully
	// transfers between accounts
	bool Transfer(int amount, SubAccount *otherAcc);

	// Returns balance of sub account
	int getBalance() const;

	// Sets linkedAccount equal to given sub account
	void setLinkedAccount(SubAccount *other);

	// Return a vector with the history of this sub account
	std::vector<std::string> getHistory() const;

private:
	// Class data
	std::string accNum;
	int balance;
	// Account used to back up this account if over drawn
	SubAccount *linkedAccount;
	// Vector to store history
	std::vector<std::string> history;
};


#endif //ASS5_SUBACCOUNT_H
