#include <vector>
#include <set>
#include <stddef.h>

class Graph {
public:
	enum MST_ALGO_TYPE {
		KRUSKAL = 1,
		PRIM,
	};

	Graph(int n);
	~Graph();

	void insertEdge(int source, int dest, int cost);
	bool hasEdge(int source, int dest, int cost);
	void dfs(int value);
	void bfs(int value);
	Graph* getMinimalSpanningTree(MST_ALGO_TYPE algo);
	std::vector<int> topologySort();

	void dump();

private:
	struct ListNode {
		int value;
		int cost;
		ListNode *next;

		ListNode() : value(-1), cost(0), next(NULL) {
		};

		ListNode(int v) : value(v), cost(0), next(NULL) {
		};

		ListNode(int v, int c) : value(v), cost(c), next(NULL) {
		};
	};

	struct Edge {
		int source;
		int dest;
		int cost;

		Edge() : source(-1), dest(-1), cost(0) {
		};

		Edge(int s, int d, int c) : source(s), dest(d), cost(c) {
		};
	};

	void doDfs(int value);

	Graph* kruskalAlgo();
	Graph* primAlgo();
	static bool edgeCmp(Edge edge1, Edge edge2);

	std::vector<int> kahnAlgo();
	int findNoPredecessorNode();

private:
	std::vector<ListNode*> headNodes;
	std::vector<Edge> edges;

	std::set<int> visited;

	std::vector<int> nodeInDegree;
};