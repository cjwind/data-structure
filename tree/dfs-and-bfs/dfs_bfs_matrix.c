// Traverse a tree by DFS
// Represent tree by matrix
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100				// 這當然有 node 數超過的問題

int tree[MAX_NODE][MAX_NODE];		// node index is from 1
int traverseOrder[MAX_NODE];
int traverseIndex = 0;
int parent[MAX_NODE];

void dfs(int n, int node) {
	traverseOrder[traverseIndex] = node;
	traverseIndex++;

	for (int i = 1; i <= n; i++) {
		if (tree[node][i] > 0) {
			parent[i] = node;
			dfs(n, i);
		}
	}
}

void bfs(int n, int node) {
	int queue[MAX_NODE] = {0};
	int head = -1, last = 0;
	int traverseOrder[MAX_NODE] = {0};
	int traverseIndex = 0;

	queue[last] = node;
	head++;
	last++;

	while (head != last) {
		int visitNode = queue[head];

		traverseOrder[traverseIndex] = visitNode;
		traverseIndex++;

		head = (head + 1) % MAX_NODE;

		for (int i = 1; i <= n; i++) {
			if (tree[visitNode][i] > 0) {
				queue[last] = i;
				last = (last + 1) % MAX_NODE;
			}
		}
	}

	for (int i = 0; i < traverseIndex; i++) {
		printf("%d\n", traverseOrder[i]);
	}
}

struct Queue {
	int node;
	struct Queue *next;
};

void enqueue(struct Queue **head, struct Queue **last, int node) {
	struct Queue *queueNode = malloc(sizeof(struct Queue));

	queueNode->node = node;
	queueNode->next = NULL;

	if ((*last) != NULL) {
		(*last)->next = queueNode;
	}

	*last = queueNode;

	if (*head == NULL) {
		*head = *last;
	}
}

int dequeue(struct Queue **head, struct Queue **last) {
	int node = -1;

	if ((*head) != NULL) {
		node = (*head)->node;
		*head = (*head)->next;
	}

	if ((*head) == NULL) {
		*last = *head;
	}

	return node;
}

int isEmpty(struct Queue **head, struct Queue **last) {
	return ((*head) != NULL);
}

void bfs2(int n, int node) {
	struct Queue *head = NULL, *last = NULL;
	int traverseOrder[MAX_NODE] = {0};
	int traverseIndex = 0;

	enqueue(&head, &last, node);

	while (isEmpty(&head, &last)) {
		int visitNode = dequeue(&head, &last);

		traverseOrder[traverseIndex] = visitNode;
		traverseIndex++;

		for (int i = 1; i <= n; i++) {
			if (tree[visitNode][i] > 0) {
				enqueue(&head, &last, i);
			}
		}
	}

	for (int i = 0; i < traverseIndex; i++) {
		printf("%d\n", traverseOrder[i]);
	}
}

int main() {
	int n = 0;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int degree = 0;

		scanf("%d", &degree);

		for (int j = 0; j < degree; j++) {
			int node = 0;
			scanf("%d", &node);
			tree[i][node] = 1;
		}
	}

	printf("DFS:\n");
	dfs(n, 2);

	for (int i = 0; i < n; i++) {
		printf("%d ", traverseOrder[i]);
	}
	printf("\n");

	for (int i = 1; i <= n; i++) {
		printf("%d's parent: %d\n", i, parent[i]);
	}

	printf("============\n");

	printf("BFS:\n");
	bfs2(n, 2);

	return 0;
}