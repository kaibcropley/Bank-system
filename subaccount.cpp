//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#include <iostream>
#include "subaccount.h"

// Constructor
SubAccount::SubAccount(std::string accNum) : accNum{accNum}, balance{0},
											 linkedAccount{nullptr},
											 history(0){
}

// Takes in SubAccount number and amount then returns if successfully
// deposited
bool SubAccount::Deposit(int amount) {
	std::string s = "D: " + accNum;
	s.append(" " + std::to_string(amount));
	s.append("\n");
	balance += amount;
	history.push_back(s);
	return true;
}

// Takes in SubAccount number and amount then returns if successfully
// withdrew
bool SubAccount::Withdraw(int amount) {
	std::string s = "W: " + accNum;
	s.append(" " + std::to_string(amount));
	if (balance < amount) {
		if (linkedAccount != nullptr &&
			(linkedAccount->balance + balance) >= amount) {
			std::string tString = "T: " + accNum;
			tString.append(" " + std::to_string(amount));
			tString.append(" " + linkedAccount->accNum);
			amount = amount - balance;
			linkedAccount->Transfer(amount, this);
			balance = 0;
			tString.append("\n");
			s.append("\n");
			history.push_back(tString);
			history.push_back(s);
			return true;
		}
		s.append(" Error: Not enough funds for withdraw\n");
		history.push_back(s);
		std::cout << "Error not enough funds for withdraw" << std::endl;
		return false;

	} else {
		balance -= amount;
		s.append("\n");
		history.push_back(s);
		return true;
	}
}

// Takes in SubAccount number and amount then returns if successfully
// transfers between accounts
bool SubAccount::Transfer(int amount, SubAccount *otherAcc) {
	std::string s = "T: " + accNum;
	s.append(" " + std::to_string(amount));
	s.append(" " + otherAcc->accNum);
	if (balance > amount) {
		balance -= amount;
		otherAcc->balance += amount;
		s.append("\n");
		otherAcc->history.push_back(s);
		history.push_back(s);
		return true;
	}
	s.append(" Error not enough funds for transfer\n");
	history.push_back(s);
	std::cout << "Error not enough funds for transfer" << std::endl;
	return false;
}

// Returns balance of sub account
int SubAccount::getBalance() const {
	return balance;
}

// Sets linked account equal to given pointer
void SubAccount::setLinkedAccount(SubAccount *other) {
	linkedAccount = other;
}

// Returns history of this sub account in a vector
std::vector<std::string> SubAccount::getHistory() const {
	return history;
}

