#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;
}

void findFinishTime(vector<vector<int> > &graph, int node, set<int> &visited, vector<pair<int, int> > &finishTime, int &t) {
	t++;
	visited.insert(node);

	for (vector<int>::iterator iter = graph[node].begin(); iter != graph[node].end(); iter++) {
		if (visited.find(*iter) == visited.end()) {
			findFinishTime(graph, *iter, visited, finishTime, t);
		}
	}

	t++;
	finishTime.push_back(pair<int, int>(node, t));
}

void dfs(vector<vector<int> > &graph, int node, set<int> &dfsTree, set<int> &visited) {
	dfsTree.insert(node);
	visited.insert(node);

	for (vector<int>::iterator iter = graph[node].begin(); iter != graph[node].end(); iter++) {
		if (visited.find(*iter) == visited.end()) {
			dfs(graph, *iter, dfsTree, visited);
		}
	}
}

vector<set<int> > findConnectedComponents(vector<vector<int> > &graph, vector<pair<int, int> > finishTime) {
	vector<set<int> > components;
	set<int> visited;

	sort(finishTime.begin(), finishTime.end(), cmp);

	for (vector<pair<int, int> >::iterator iter = finishTime.begin(); iter != finishTime.end(); iter++) {
		int node = iter->first;

		if (visited.find(node) == visited.end()) {
			set<int> dfsTree;

			dfs(graph, node, dfsTree, visited);
			components.push_back(dfsTree);

			for (set<int>::iterator iter = dfsTree.begin(); iter != dfsTree.end(); iter++) {
				visited.insert(*iter);
			}
		}
	}

	return components;
}

int main() {
	int V = 0, E = 0;

	cin >> V >> E;

	vector<vector<int> > graph(V + 1, vector<int>());
	vector<vector<int> > graphT(V + 1, vector<int>());

	for (int i = 0; i < E; i++) {
		int u, v;
		cin >> u >> v;

		graph[u].push_back(v);
		graphT[v].push_back(u);
	}

	set<int> visited;
	vector<pair<int, int> > finishTime;
	int t = 0;
	findFinishTime(graph, 1, visited, finishTime, t);

	vector<set<int> > components = findConnectedComponents(graphT, finishTime);

	for (int i = 0; i < components.size(); i++) {
		for (set<int>::iterator iter = components[i].begin(); iter != components[i].end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}

	return 0;
}
