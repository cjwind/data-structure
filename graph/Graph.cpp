#include "Graph.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

Graph::Graph(int n) {
	for (int i = 0; i < n; i++) {
		headNodes.push_back(new ListNode(i));
		nodeInDegree.push_back(0);
	}
}

Graph::~Graph() {
	ListNode *node = NULL, *nextNode = NULL;

	for (vector<ListNode*>::iterator iter = headNodes.begin(); iter != headNodes.end(); iter++) {
		node = (*iter);

		while (node) {
			nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}
}

void Graph::insertEdge(int source, int dest, int cost) {
	ListNode *node = headNodes[source]->next;
	ListNode *lastNode = headNodes[source];

	while (node) {
		if (node->value == dest) {
			return;
		}

		lastNode = node;
		node = node->next;
	}

	ListNode *newNode = new ListNode(dest, cost);
	lastNode->next = newNode;

	edges.push_back(Edge(source, dest, cost));

	nodeInDegree[dest]++;
}

bool Graph::hasEdge(int source, int dest, int cost) {
	for (vector<Edge>::iterator iter = edges.begin(); iter != edges.end(); iter++) {
		if ((*iter).source == source && (*iter).dest == dest && (*iter).cost == cost) {
			return true;
		}
	}

	return false;
}

void Graph::dfs(int value) {
	visited.clear();
	doDfs(value);
}

void Graph::doDfs(int value) {
	cout << value << endl;
	visited.insert(value);

	ListNode *node = headNodes[value]->next;

	while (node) {
		if (visited.find(node->value) == visited.end()) {
			doDfs(node->value);
		}

		node = node->next;
	}
}

void Graph::bfs(int value) {
	queue<int> queue;
	set<int> visited;

	queue.push(value);
	visited.insert(value);		// 塞進 queue 就設成 visited 避免重複塞已經在 queue 裡卻還沒實際 visit 到的 node

	while (!queue.empty()) {
		int currValue = queue.front();
		queue.pop();

		cout << currValue << endl;

		ListNode *node = headNodes[currValue]->next;
		while (node) {
			if (visited.find(node->value) == visited.end()) {
				queue.push(node->value);
				visited.insert(node->value);
			}

			node = node->next;
		}
	}
}

Graph* Graph::getMinimalSpanningTree(MST_ALGO_TYPE algo) {
	switch (algo) {
		case KRUSKAL:
			return kruskalAlgo();
		case PRIM:
			return primAlgo();
		default:
			return NULL;
	}
}

Graph* Graph::kruskalAlgo() {
	sort(edges.begin(), edges.end(), edgeCmp);

	int n = headNodes.size();
	int nodeSet[n];

	for (int i = 0; i < n; i++) {
		nodeSet[i] = i;
	}

	Graph *mst = new Graph(n);
	int edgeCount = 0;

	for (vector<Edge>::iterator iter = edges.begin(); iter != edges.end(); iter++) {
		if (nodeSet[iter->source] != nodeSet[iter->dest]) {
			mst->insertEdge(iter->source, iter->dest, iter->cost);

			if (this->hasEdge(iter->dest, iter->source, iter->cost)) {		// undirected edge
				mst->insertEdge(iter->dest, iter->source, iter->cost);
			}

			edgeCount++;

			int destNodeSet = nodeSet[iter->dest];
			for (int i = 0; i < n; i++) {
				if (nodeSet[i] == destNodeSet) {
					nodeSet[i] = nodeSet[iter->source];
				}
			}
		}

		if (edgeCount == n - 1) {
			break;
		}
	}

	return mst;
}

Graph* Graph::primAlgo() {
	int n = headNodes.size();
	vector<ListNode*> mstNodes;
	Graph *mst = new Graph(n);
	int nodeSet[n];

	memset(nodeSet, 0, n * sizeof(int));

	mstNodes.push_back(headNodes[0]);		// 從第一個 node 開始
	nodeSet[0] = 1;

	for (int edgeCount = 0; edgeCount < n - 1; edgeCount++) {
		int minCost = -1;		// assume cost is postivie, so -1 is a special number
		int source = -1, dest = -1;

		for (vector<ListNode*>::iterator iter = mstNodes.begin(); iter != mstNodes.end(); iter++) {
			ListNode *node = (*iter)->next;

			while (node) {
				if (nodeSet[node->value] == 1) {
					node = node->next;
					continue;
				}

				if (minCost == -1 || node->cost < minCost) {
					minCost = node->cost;
					source = (*iter)->value;
					dest = node->value;
				}

				node = node->next;
			}
		}

		mst->insertEdge(source, dest, minCost);

		if (this->hasEdge(dest, source, minCost)) {		// undirected edge
			mst->insertEdge(dest, source, minCost);
		}

		mstNodes.push_back(headNodes[dest]);
		nodeSet[dest] = 1;
	}

	return mst;
}

bool Graph::edgeCmp(Edge edge1, Edge edge2) {
	return (edge1.cost < edge2.cost);
}

vector<int> Graph::topologySort() {
	return kahnAlgo();
}

vector<int> Graph::kahnAlgo() {
	vector<int> sorted;

	for (int i = 0; i < headNodes.size(); i++) {
		int node = findNoPredecessorNode();			// nodeInDegree 用 map 應該可以比較快

		if (node == -1) {		// there's cycle
			return vector<int>();
		}

		sorted.push_back(node);
		nodeInDegree[node] = -1;

		ListNode *currNode = headNodes[node]->next;
		while (currNode) {
			nodeInDegree[currNode->value]--;
			currNode = currNode->next;
		}
	}

	return sorted;
}

int Graph::findNoPredecessorNode() {
	for (int i = 0; i < headNodes.size(); i++) {
		if (nodeInDegree[i] == 0) {
			return i;
		}
	}

	return -1;
}

void Graph::dump() {
	ListNode *node = NULL;

	for (vector<ListNode*>::iterator iter = headNodes.begin(); iter != headNodes.end(); iter++) {
		node = (*iter);

		cout << node->value << ": ";

		node = node->next;
		while (node) {
			cout << node->value << " ";
			node = node->next;
		}

		cout << endl;
	}
}

int main() {
	int isDirtected = 0;
	int n = 0, e = 0;

	cin >> isDirtected;
	cin >> n;
	cin >> e;

	Graph graph(n);

	for (int i = 0; i < e; i++) {
		int n1 = 0, n2 = 0, cost = 0;
		cin >> n1 >> n2 >> cost;
		graph.insertEdge(n1, n2, cost);

		if (!isDirtected) {
			graph.insertEdge(n2, n1, cost);
		}
	}

	graph.dump();

	if (!isDirtected) {
		int startFrom = 0;
		cin >> startFrom;

		cout << "dfs from node " << startFrom << ":" << endl;
		graph.dfs(startFrom);

		cout << "bfs from node " << startFrom << ":" << endl;
		graph.bfs(startFrom);

		cout << "MST by kruskal's algo:" << endl;
		Graph *mst = graph.getMinimalSpanningTree(Graph::KRUSKAL);
		mst->dump();

		cout << "MST by prim's algo:" << endl;
		mst = graph.getMinimalSpanningTree(Graph::PRIM);
		mst->dump();
	}
	else {
		vector<int> topologySortResult = graph.topologySort();
		cout << "Topology sort: ";
		for (vector<int>::iterator iter = topologySortResult.begin(); iter != topologySortResult.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}

	return 0;
}