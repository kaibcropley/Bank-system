//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#ifndef ASS5_BSTREE_H
#define ASS5_BSTREE_H

#include <iostream>
#include "account.h"

class BSTree {
public:
	// Constructor
	BSTree();

	// Destructor
	~BSTree();

	// Adds a new account to tree
	bool Insert(Account *newAcc);

	// Retrieve object, first parameter is the ID of the account
	// Second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int &accID, Account *&foundAcc) const;

	// displays the contents of a tree to cout
	void Display() const;

	// Deletes all nodes in this tree
	void Empty();

	// Returns true if is empty
	bool isEmpty() const;

private:
	// Node structure for within tree.
	struct Node {
		Account *pAcct;
		Node *right;
		Node *left;
		Node *parent;
	};
	Node *root;

	// Used for printing out binary tree in post order
	void postOrder(Node *curr, int indent) const;

	// Recursive method to help add a new account to the tree
	bool addHelper(Node *newNode, Account *newAcc);
};


#endif //ASS5_BSTREE_H
