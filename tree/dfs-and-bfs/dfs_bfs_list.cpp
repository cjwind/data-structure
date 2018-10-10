// Traverse a binary tree by DFS
// Represent tree by linked list
// diff -B <( ls -1 / ) <( ls -1 ~ )  diff 兩個 command 結果
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>

#define MAX_NODE 100

struct Node {
	int value;
	struct Node *leftChild;
	struct Node *rightChild;
};

struct Node *traverseOrder[MAX_NODE];
int traverseIndex = 0;

void dfs(struct Node *node) {
	traverseOrder[traverseIndex] = node;
	traverseIndex++;

	if (node->leftChild != NULL) {
		dfs(node->leftChild);
	}

	if (node->rightChild != NULL) {
		dfs(node->rightChild);
	}
}

void dfs2(struct Node *node) {
	std::stack<struct Node*> stack;
	struct Node *traverseOrder[MAX_NODE];
	int traverseIndex = 0;

	stack.push(node);

	while (!stack.empty()) {
		struct Node *visitNode = stack.top();
		stack.pop();

		traverseOrder[traverseIndex] = visitNode;
		traverseIndex++;

		if (visitNode->rightChild != NULL) {
			stack.push(visitNode->rightChild);
		}

		if (visitNode->leftChild != NULL) {
			stack.push(visitNode->leftChild);
		}
	}

	for (int i = 0; i < traverseIndex; i++) {
		printf("%d\n", traverseOrder[i]->value);
	}
}

void bfs(struct Node *node) {
	std::queue<struct Node*> queue;
	struct Node *traverseOrder[MAX_NODE];
	int traverseIndex = 0;

	queue.push(node);

	while (!queue.empty()) {
		struct Node *visitNode = queue.front();
		queue.pop();

		traverseOrder[traverseIndex] = visitNode;
		traverseIndex++;

		if (visitNode->leftChild) {
			queue.push(visitNode->leftChild);
		}

		if (visitNode->rightChild) {
			queue.push(visitNode->rightChild);
		}
	}

	for (int i = 0; i < traverseIndex; i++) {
		printf("%d\n", traverseOrder[i]->value);
	}
}

int main() {
	int n = 0;
	int rootValue = 0;
	struct Node *nodes[MAX_NODE];

	scanf("%d", &n);
	scanf("%d", &rootValue);

	for (int i = 1; i <= n; i++) {
		struct Node* node = (struct Node*)malloc(sizeof(struct Node));
		node->leftChild = node->rightChild = NULL;
		node->value = i;
		nodes[i] = node;
	}

	for (int i = 1; i <= n; i++) {
		int degree = 0;

		scanf("%d", &degree);

		for (int j = 0; j < degree; j++) {
			int value = 0;

			scanf("%d", &value);

			if (nodes[i]->leftChild == NULL) {
				nodes[i]->leftChild = nodes[value];
			}
			else {
				nodes[i]->rightChild = nodes[value];
			}
		}
	}

	printf("DFS:\n");
	dfs2(nodes[rootValue]);

	// for (int i = 0; i < n; i++) {
	// 	printf("%d\n", traverseOrder[i]->value);
	// }

	printf("============\n");

	printf("BFS:\n");
	bfs(nodes[rootValue]);

	for (int i = 1; i <= n; i++) {
		free(nodes[i]);
	}

	return 0;
}
