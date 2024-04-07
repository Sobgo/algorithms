#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N, M;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int> &parent) {
	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;

	queue<pair<int, int>> q;
	q.push({s, INF});

	while (!q.empty()) {
		int cur = q.front().first;
		int flow = q.front().second;
		q.pop();

		for (int next : adj[cur]) {
			if (parent[next] == -1 && capacity[cur][next]) {
				parent[next] = cur;
				int new_flow = min(flow, capacity[cur][next]);
				if (next == t) return new_flow;
				q.push({next, new_flow});
			}
		}
	}

	return 0;
}

int maxflow(int s, int t) {
	int flow = 0;
	vector<int> parent(N);
	int new_flow;

	while (new_flow = bfs(s, t, parent)) {
		flow += new_flow;
		int cur = t;

		while (cur != s) {
			int prev = parent[cur];
			capacity[prev][cur] -= new_flow;
			capacity[cur][prev] += new_flow;
			cur = prev;
		}
	}

	return flow;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, c, t;
	cin >> t;

	for (int tc = 0; tc < t; ++tc) {
		cin >> n >> m >> c >> M;
		N = n + m + 2;

		capacity.assign(N, vector<int>(N, 0));
		adj.assign(N, vector<int>());

		int s = adj.size() - 2, e = adj.size() - 1;

		for (int i = 0; i < n; ++i) {
			adj[s].push_back(i);
			adj[i].push_back(s);
			capacity[s][i] = 1;
		}

		for (int i = 0; i < m; ++i) {
			adj[i + n].push_back(e);
			adj[e].push_back(i + n);
			capacity[i + n][e] = c;
		}

		int a, b;
		for (int i = 0; i < M; ++i) {
			cin >> a >> b;
			--a, --b;
			adj[a].push_back(b + n);
			adj[b + n].push_back(a);
			capacity[a][b + n] = 1;
		}

		cout << maxflow(s, e) << '\n';
	}

	return 0;
}
