#include <stddef.h>
#include <vector>

class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();

	bool search(int value);
	int searchByRank(int rank);
	void insert(int value);
	void remove(int value);
	void dump();

private:
	struct Node {
		int value;
		Node *leftChild;
		Node *rightChild;
		Node *parent;

		Node() : value(0), leftChild(NULL), rightChild(NULL), parent(NULL) {
		};

		Node(int v) : value(v), leftChild(NULL), rightChild(NULL), parent(NULL) {
		};
	};

	Node *searchNode(int value);
	Node *findSuccessor(Node *node);
	Node *findPredecessor(Node *node);

	void dfs(Node *node);

private:
	Node *root;
	std::vector<Node*> visitNodes;
};