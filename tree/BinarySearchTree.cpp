#include "BinarySearchTree.h"
#include <vector>
#include <iostream>

using namespace std;

BinarySearchTree::BinarySearchTree() : root(NULL) {
}

BinarySearchTree::~BinarySearchTree() {
	visitNodes.clear();
	dfs(root);

	for (vector<Node*>::iterator iter = visitNodes.begin(); iter != visitNodes.end(); iter++) {
		delete (*iter);
	}
}

bool BinarySearchTree::search(int value) {
	return (searchNode(value) != NULL);
}

BinarySearchTree::Node* BinarySearchTree::searchNode(int value) {
	Node *currNode = root;

	while (currNode) {
		if (value == currNode->value) {
			return currNode;
		}
		else if (value < currNode->value) {
			currNode = currNode->leftChild;
		}
		else {
			currNode = currNode->rightChild;
		}
	}

	return NULL;
}

void BinarySearchTree::insert(int value) {
	if (root == NULL) {
		root = new Node(value);
		return;
	}

	Node *parentNode = root;

	while (parentNode) {
		if (value == parentNode->value) {
			return;
		}
		else if (value < parentNode->value) {
			if (parentNode->leftChild) {
				parentNode = parentNode->leftChild;
			}
			else {
				Node *node = new Node(value);
				parentNode->leftChild = node;
				node->parent = parentNode;
				return;
			}
		}
		else {
			if (parentNode->rightChild) {
				parentNode = parentNode->rightChild;
			}
			else {
				Node *node = new Node(value);
				parentNode->rightChild = node;
				node->parent = parentNode;
				return;
			}
		}
	}
}

void BinarySearchTree::remove(int value) {
	Node *node = searchNode(value);

	if (node != NULL) {
		if (node->leftChild == NULL && node->rightChild == NULL) {
			if (node->parent->leftChild == node) {
				node->parent->leftChild = NULL;
			}
			else if (node->parent->rightChild == node) {
				node->parent->rightChild = NULL;
			}

			delete node;
		}
		else if (node->leftChild != NULL && node->rightChild != NULL) {
			// 為了在刪除 node 後維持 BST 的性質，把 successor 的值放到 node 的位置來 (等同刪除 node 的 value)，delete successor node
			Node *successor = findSuccessor(node);

			node->value = successor->value;

			if (successor->leftChild == NULL && successor->rightChild == NULL) {
				successor->parent->leftChild = NULL;		// successor 必然是其 parent 的 left child
			}
			else {		// have only one child
				successor->parent->leftChild = successor->rightChild;		// successor 必然只有 right child
			}

			delete successor;
		}
		else {		// only one child
			if (node->parent->leftChild == node) {
				node->parent->leftChild = (node->leftChild) ? node->leftChild : node->rightChild;
			}
			else if (node->parent->rightChild == node) {
				node->parent->rightChild = (node->leftChild) ? node->leftChild : node->rightChild;
			}

			delete node;
		}
	}
}

// Successor is smallest node in right subtree
BinarySearchTree::Node* BinarySearchTree::findSuccessor(Node *node) {
	Node *currNode = node->rightChild;

	while (currNode->leftChild) {
		currNode = currNode->leftChild;
	}

	return currNode;
}

// Predecessor is biggest node in left subtree
BinarySearchTree::Node* BinarySearchTree::findPredecessor(Node *node) {
	Node *currNode = node->leftChild;

	while (currNode->rightChild) {
		currNode = currNode->rightChild;
	}

	return currNode;
}

void BinarySearchTree::dump() {
	visitNodes.clear();

	dfs(root);

	for (vector<Node*>::iterator iter = visitNodes.begin(); iter != visitNodes.end(); iter++) {
		cout << (*iter)->value << " ";
	}
	cout << endl;
}

void BinarySearchTree::dfs(Node *node) {
	if (node) {
		visitNodes.push_back(node);

		if (node->leftChild) {
			dfs(node->leftChild);
		}

		if (node->rightChild) {
			dfs(node->rightChild);
		}
	}
}

int main() {
	int values[] = {4, 2, 8, 54, 86, 22, 9, 3, 21, 22, 100, 11, 70, 60, 65};
	BinarySearchTree BTree;

	for (int i = 0; i < sizeof(values) / sizeof(int); i++) {
		BTree.insert(values[i]);
	}

	BTree.dump();
	BTree.dump();

	cout << "Search 9: " << BTree.search(9) << endl;
	cout << "Search 100: " << BTree.search(100) << endl;
	cout << "Search 5: " << BTree.search(5) << endl;
	cout << "Search 3: " << BTree.search(3) << endl;

	BTree.remove(54);
	cout << "After remove 54: ";
	BTree.dump();

	BTree.remove(11);
	cout << "After remove 11: ";
	BTree.dump();

	BTree.remove(2);
	cout << "After remove 2: ";
	BTree.dump();

	return 0;
}