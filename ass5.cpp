//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#include <iostream>
#include <cassert>
#include "account.h"
#include "bstree.h"
#include "bank.h"

using namespace std;

// Test all functionality of SubAccount class methods
void SubAccountTest() {
	SubAccount s("10101");
	assert(s.Deposit(500));
	assert(!s.Withdraw(1000));
	assert(s.Withdraw(200));
	assert(s.getBalance() == 300);

	SubAccount linked("10100");
	assert(linked.Deposit(300));
	s.setLinkedAccount(&linked);
	assert(s.Withdraw(500));
	assert(s.getBalance() == 0);
	assert(linked.getBalance() == 100);

//	vector<std::string> v = s.getHistory();
//	for (int i{0}; i < v.size(); i++) {
//		cout << v[i];
//	}
}

// Test all functionality of Account class methods
void AccountTest() {
	Account a("Kaib", "Cropley", 1234);
	assert(!a.Withdraw(0, 1000));
	assert(a.Deposit(0, 1000));
	assert(a.Deposit(1, 1000));
	assert(a.Withdraw(0, 200));
	assert(a.GetAccountID() == 1234);
	assert(a.GetName() == "Kaib Cropley");

	SubAccount subAcc("12202");
	assert(subAcc.Deposit(1000));
	assert(a.Transfer(1, 200, &subAcc));

	Account a2("Kaib", "Cropley", 9999);
	Account a3("Kaib", "Cropley", 9999);

	assert(a2 > a);
	assert(a < a2);
	assert(a2 == a3);

//	a.printHistory();
//	cout << a.GetHistory();
}

// Test all BSTree functionality
void BSTreeTest() {
	BSTree tree;

	Account *a = new Account("First", "Last", 500);
	tree.Insert(a);
	int nums[10] = {5000, 4330, 2620, 2430, 2130, 4930, 3120, 1120, 7290, 8000};
	for (int i{0}; i < 10; i++) {
		Account *a1 = new Account("First", "Last", nums[i]);
		assert(tree.Insert(a1));
	}

//	tree.Display();
	assert(tree.Retrieve(5000, a));
	assert(tree.Retrieve(4330, a));
	assert(tree.Retrieve(2620, a));
	assert(tree.Retrieve(8000, a));
	assert(!tree.Retrieve(1000, a));
	assert(!tree.Retrieve(10000, a));
	assert(!tree.Retrieve(4, a));

	assert(!tree.isEmpty());
	tree.Empty();
	assert(tree.isEmpty());
	assert(!tree.Retrieve(5000, a));
	assert(!tree.Retrieve(4330, a));
	assert(!tree.Retrieve(8000, a));
}

// Test all Bank functions
void BankTest(const string &fileName) {
	Bank b;
	std::queue<std::string> q;
	q = b.readFile(fileName);
	b.execute(q);
}

// Runs all test functions
void testAll(int argc, char *argv[]) {
	SubAccountTest();
	AccountTest();
	BSTreeTest();
	for (int i{1}; i < argc; i++) {
		BankTest(argv[i]);
		std::cout << std::endl << "--------New Test--------"
				  << std::endl << std::endl;
	}

}

int main(int argc, char *argv[]) {
	testAll(argc, argv);
	std::cout << "Finished running." << std::endl;
	return 0;
}