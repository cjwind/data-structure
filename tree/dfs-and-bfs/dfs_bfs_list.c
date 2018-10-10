// Traverse a binary tree by DFS
// Represent tree by linked list
// diff -B <( ls -1 / ) <( ls -1 ~ )  diff 兩個 command 結果
#include <stdio.h>
#include <stdlib.h>

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

void bfs(struct Node *node) {
	struct Node *queue[MAX_NODE];
	int head = -1, last = 0;
	struct Node *traverseOrder[MAX_NODE];
	int traverseIndex = 0;

	queue[last] = node;
	head++;
	last++;

	while (head != last) {
		struct Node *visitNode = queue[head];

		head = (head + 1) % MAX_NODE;

		traverseOrder[traverseIndex] = visitNode;
		traverseIndex++;

		if (visitNode->leftChild) {
			queue[last] = visitNode->leftChild;
			last = (last + 1) % MAX_NODE;
		}

		if (visitNode->rightChild) {
			queue[last] = visitNode->rightChild;
			last = (last + 1) % MAX_NODE;
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
		struct Node* node = malloc(sizeof(struct Node));
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
	dfs(nodes[rootValue]);

	for (int i = 0; i < n; i++) {
		printf("%d\n", traverseOrder[i]->value);
	}

	printf("============\n");

	printf("BFS:\n");
	bfs(nodes[rootValue]);

	for (int i = 1; i <= n; i++) {
		free(nodes[i]);
	}

	return 0;
}
