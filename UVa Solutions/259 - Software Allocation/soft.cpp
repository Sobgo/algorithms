#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647 / 2;
const int ADJ_SIZE = 26 + 10 + 2;

int n;
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
	vector<int> parent(n);
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

string encode(int total) {
	int mf = maxflow(ADJ_SIZE - 2, ADJ_SIZE - 1);

	if (mf < total) {
		return "!";
	} else {
		string encoded(10, '_');

		for (int i = 10; i < 36; ++i) {
			for (int next : adj[i]) {
				if (capacity[i][next] == 0) {
					encoded[next] = 'A' + i - 10;
				}
			}
		}

		return encoded;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int node, weight;
	string str;

	n = ADJ_SIZE;
	capacity.assign(ADJ_SIZE, vector<int>(ADJ_SIZE, 0));
	adj.assign(ADJ_SIZE, vector<int>());
	int total = 0;

	int s = ADJ_SIZE - 2, e = ADJ_SIZE - 1;

	while (getline(cin, str)) {
		if (str.size() == 0) {
			cout << encode(total) << '\n';

			capacity.assign(ADJ_SIZE, vector<int>(ADJ_SIZE, 0));
			adj.assign(ADJ_SIZE, vector<int>());
			total = 0;
		} else {
			node = str[0] - 'A' + 10;
			weight = stoi(str.substr(1, 1));
			total += weight;

			adj[s].push_back(node);
			adj[node].push_back(s);
			capacity[s][node] = weight;

			for (int i = 3; i < str.size(); ++i) {
				if (isdigit(str[i])) {
					int next = stoi(str.substr(i, 1));
					adj[node].push_back(next);
					adj[next].push_back(node);
					capacity[node][next] = 1;
				}
			}

			for (int i = 0; i < 10; ++i) {
				adj[i].push_back(e);
				adj[e].push_back(i);
				capacity[i][e] = 1;
			}
		}
	}

	if (str.size() == 0) {
		cout << encode(total) << '\n';
	}

	return 0;
}
