#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int find_source(vector<vector<int>> &adj, int start) {
	queue<int> q;
	vector<bool> visited(adj.size(), false);

	q.push(start);
	int node = start;

	while (!q.empty()) {
		node = q.front();
		q.pop();

		for (auto &e : adj[node]) {
			if (!visited[e]) {
				visited[e] = true;
				q.push(e);
				break;
			}
		}
	}

	return node;
}

void bfs(vector<vector<int>> &adj, vector<bool> &visited, int start) {
	queue<int> q;
	q.push(start);
	visited[start] = true;

	int node;

	while (!q.empty()) {
		node = q.front();
		q.pop();

		for (auto &e : adj[node]) {
			if (!visited[e]) {
				visited[e] = true;
				q.push(e);
			}
		}
	}
}

int solve() {
	int n, m;
	int total = 0;

	cin >> n >> m;

	vector<vector<int>> adj(n);
	vector<vector<int>> rev(n);
	vector<bool> down(n, false);

	int a, b;

	for (int j = 0; j < m; ++j) {
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		rev[b].push_back(a);
	}

	for (int i = 0; i < adj.size(); ++i) {
		if (!down[i]) {
			int source = find_source(rev, i);

			if (!down[source]) {
				bfs(adj, down, source);
				total++;
			}
		}
	}

	return total;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int x;
	cin >> x;

	for (int i = 0; i < x; ++i) {
		cout << solve() << "\n";
	}

	return 0;
}
