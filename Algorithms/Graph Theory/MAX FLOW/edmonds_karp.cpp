#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;

int N, M;
vector<vector<int>> ADJ, CAP;

int bfs(int s, int t, vector<int> &parent) {
	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;

	queue<pair<int, int>> q;
	q.push({s, INF});

	while (!q.empty()) {
		int cur = q.front().first;
		int flow = q.front().second;
		q.pop();

		for (int next : ADJ[cur]) {
			if (parent[next] == -1 && CAP[cur][next]) {
				parent[next] = cur;
				int new_flow = min(flow, CAP[cur][next]);
				if (next == t) return new_flow;
				q.push({next, new_flow});
			}
		}
	}

	return 0;
}

int maxflow(int s, int t) {
	int new_flow, flow = 0;
	vector<int> parent(N);

	while (new_flow = bfs(s, t, parent)) {
		flow += new_flow;
		int cur = t;

		while (cur != s) {
			int prev = parent[cur];
			CAP[prev][cur] -= new_flow;
			CAP[cur][prev] += new_flow;
			cur = prev;
		}
	}

	return flow;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	CAP.assign(N, vector<int>(N, 0));
	ADJ.assign(N, vector<int>());
	vector<vector<int>> adj_copy = ADJ;

	int a, b, w;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> w;
		ADJ[a].push_back(b);
		ADJ[b].push_back(a);
		CAP[a][b] = w;

		adj_copy[a].push_back(b);
	}

	cout << "Max flow value: " << maxflow(0, N - 1) << "\n";

	cout << "Flow on edges:\n";
	for (int i = 0; i < N; ++i) {
		for (int j : adj_copy[i]) {
			cout << i << " -> " << j << " w: " << CAP[j][i] << "\n";
		}
	}

	return 0;
}
