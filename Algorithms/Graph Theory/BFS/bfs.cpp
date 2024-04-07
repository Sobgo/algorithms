#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M;
vector<vector<int>> ADJ;

vector<int> BFS(int start) {
	queue<int> q;
	vector<bool> visited(N, false);

	// for path reconstruction
	vector<int> parents(N, -1);

	// set start as initial node
	q.push(start);
	visited[start] = true;

	int cur;

	while (!q.empty()) {
		cur = q.front();
		q.pop();

		// add all unvisited neighbours to queue
		for (int next : ADJ[cur]) {
			if (!visited[next]) {
				q.push(next);
				visited[next] = true;

				parents[next] = cur;
			}
		}
	}

	return parents;
}

vector<int> path(int start, int end) {
	vector<int> path;
	vector<int> parents = BFS(start);

	// reconstruct path from end to start
	for (int i = end; i != -1; i = parents[i]) {
		path.push_back(i);
	}

	// and reverse it
	reverse(path.begin(), path.end());

	// if path after reversing doesn't start in start
	// then path doesn't exist so return empty vector
	if (path[0] != start) return vector<int>();
	return path;
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

	// find shortest path from start to end
	int start, end;
	cin >> start >> end;

	vector<int> p = path(start, end);
	for (int i : p) cout << i << " ";
	cout << "\n";

	return 0;
}
