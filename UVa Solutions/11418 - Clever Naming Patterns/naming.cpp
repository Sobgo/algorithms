#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N, M;
vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<vector<string>> names;

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
				if (next == t)
					return new_flow;
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

	int n, m, t;
	string str;

	cin >> t;

	for (int tc = 0; tc < t; ++tc) {
		cin >> n;
		N = n + 26 + 2;

		capacity.assign(N, vector<int>(N, 0));
		names.assign(N, vector<string>(N, ""));
		adj.assign(N, vector<int>());

		int s = adj.size() - 2, e = adj.size() - 1;

		for (int i = 0; i < n; ++i) {
			cin >> m;

			for (int j = 0; j < m; ++j) {
				cin >> str;

				str[0] = toupper(str[0]);
				for (int k = 1; k < str.size(); ++k) {
					str[k] = tolower(str[k]);
				}

				int letter = str[0] - 'A' + n;
				adj[i].push_back(letter);
				adj[letter].push_back(i);
				capacity[i][letter] = 1;
				names[i][letter] = str;
			}
		}

		for (int i = 0; i < n; ++i) {
			adj[s].push_back(i);
			adj[i].push_back(s);
			capacity[s][i] = 1;
		}

		for (int i = n; i < n + 26; ++i) {
			adj[i].push_back(e);
			adj[e].push_back(i);
			capacity[i][e] = 1;
		}

		maxflow(s, e);

		cout << "Case #" << tc + 1 << ":\n";

		vector<string> ans;

		for (int i = 0; i < n; ++i) {
			for (int j = n; j < n + 26; ++j) {
				if (capacity[i][j] == 0 && capacity[j][i] != 0) {
					ans.push_back(names[i][j]);
					break;
				}
			}
		}

		sort(ans.begin(), ans.end());

		for (int i = 0; i < ans.size(); ++i) {
			cout << ans[i] << '\n';
		}
	}

	return 0;
}
