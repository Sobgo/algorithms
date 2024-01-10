#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector < vector <int> > ADJ;

void DFS(int node, vector <bool> &visited) {
	if (visited[node]) return;
	visited[node] = true;

	cout << node << ' ';

	for (int next : ADJ[node]) {
		DFS(next, visited);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// N = number of nodes, M = number of edges
	cin >> N >> M;

	// read adjacency list
	ADJ.resize(N);

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		ADJ[a].push_back(b);
		ADJ[b].push_back(a);
	}

	int start;
	cin >> start;

	cout << "DFS traversal: ";
	vector <bool> visited(N, false);
	DFS(start, visited);

	return 0;
}
