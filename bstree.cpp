//
// Created by Kaib Cropley on 5/18/2018.
// Edited last on 5/28/2018.
//

#include <iostream>
#include "bstree.h"

// Constructor
BSTree::BSTree() : root{nullptr} {
}

// Destructor
BSTree::~BSTree() {
	Node *curr = root;
	Node *prev = nullptr;
	while (curr != nullptr) {
		if (curr->left == nullptr && curr->right == nullptr) {
			prev = curr->parent;
			if (prev != nullptr && prev->left == curr) {
				prev->left = nullptr;
			}
			if (prev != nullptr && prev->right == curr) {
				prev->right = nullptr;
			}
			delete curr->pAcct;
			delete curr;
			curr = prev;
		} else if (curr->left != nullptr) {
			curr = curr->left;
		} else if (curr->right != nullptr) {
			curr = curr->right;
		}
	}
}

// Adds a new account to tree
bool BSTree::Insert(Account *newAcc) {
	return addHelper(root, newAcc);
}

// Recursive method to help add a new account to the tree
bool BSTree::addHelper(Node *curr, Account *newAcc) {
	if (isEmpty()) {
		root = new Node();
		root->pAcct = newAcc;
		return true;
	}
	if (curr->pAcct->GetAccountID() > newAcc->GetAccountID()) {
		if (curr->left == nullptr) {
			curr->left = new Node();
			curr->left->pAcct = newAcc;
			curr->left->parent = curr;
			return true;
		} else {
			return addHelper(curr->left, newAcc);
		}
	} else {
		if (curr->right == nullptr) {
			curr->right = new Node();
			curr->right->pAcct = newAcc;
			curr->right->parent = curr;
			return true;
		} else {
			return addHelper(curr->right, newAcc);
		}
	}
}

// Returns true if is empty
bool BSTree::isEmpty() const {
	return root == nullptr;
}

// displays the contents of a tree to cout
void BSTree::Display() const {
	postOrder(root, 16);
}

// Used for printing out binary tree in post order
void BSTree::postOrder(Node *curr, int indent) const {
	if (curr != nullptr) {
		if (curr->left) {
			postOrder(curr->left, indent + 4);
		}
		if (curr->right) {
			postOrder(curr->right, indent + 4);
		}
		for (int i{0}; i < indent; i++) {
			std::cout << " ";
		}
		std::cout << curr->pAcct->GetAccountID() << "\n ";
	}
}

// Retrieve object, first parameter is the ID of the account
// Second parameter holds pointer to found object, NULL if not found
bool BSTree::Retrieve(const int &accID, Account *&foundAcc) const {
	if (isEmpty()) {
		return false;
	}

	Node *curr = root;
	while (curr) {
		if (curr->pAcct->GetAccountID() == accID) {
			foundAcc = curr->pAcct;
			return true;
		} else if (curr->pAcct->GetAccountID() > accID) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}
	return false;

}

// Deletes all nodes in this tree
void BSTree::Empty() {
	Node *curr = root;
	Node *prev = nullptr;
	while (curr != nullptr) {
		if (curr->left == nullptr && curr->right == nullptr) {
			prev = curr->parent;
			if (prev != nullptr && prev->left == curr) {
				prev->left = nullptr;
			}
			if (prev != nullptr && prev->right == curr) {
				prev->right = nullptr;
			}
			delete curr->pAcct;
			delete curr;
			curr = prev;
		} else if (curr->left != nullptr) {
			curr = curr->left;
		} else if (curr->right != nullptr) {
			curr = curr->right;
		}
	}
	root = nullptr;
}

