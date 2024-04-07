#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

void BFS(int start, vvi &adj, vb &visited) {
	queue<int> q;
	int node;

	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		node = q.front();
		q.pop();

		for (auto next : adj[node]) {
			if (!visited[next]) {
				visited[next] = true;
				q.push(next);
			}
		}
	}
}

vvi read_adj(int n) {
	int a, b;
	vvi adj(n);

	string s;

	getline(cin, s); // trailing newline

	while (getline(cin, s) && !s.empty()) {
		a = s[0] - 'A';
		b = s[1] - 'A';

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	return adj;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i) {
		char c;
		int n;
		cin >> c;

		n = c - 'A' + 1;

		vvi adj = read_adj(n);
		vb visited(n, false);

		int total = 0;

		for (int i = 0; i < n; ++i) {
			if (!visited[i]) {
				BFS(i, adj, visited);
				total++;
			}
		}

		cout << total << "\n";
		if (i != t - 1) cout << "\n";
	}

	return 0;
}
