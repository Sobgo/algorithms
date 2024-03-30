#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N, M;
vector <vector <int>> capacity;
vector <vector <int>> adj;

int bfs(int s, int t, vector <int> &parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue <pair <int, int>> q;
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
    vector <int> parent(N);
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

void print_mincut() {
	vector <bool> visited(N);
	queue <int> q;

	q.push(0);
	visited[0] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next : adj[cur]) {
			if (capacity[cur][next] && !visited[next]) {
				visited[next] = true;
				q.push(next);
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		if (visited[i]) {
			for (int next : adj[i]) {
				if (!visited[next]) {
					cout << i + 1 << ' ' << next + 1 << '\n';
				}
			}
		}
	}
}
	
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> N >> M) {
		if (N == 0 && M == 0) break;

		capacity.assign(N, vector<int>(N, 0));
        adj.assign(N, vector<int>());

		int a, b, w;
		for (int i = 0; i < M; ++i) {
			cin >> a >> b >> w;
			--a, --b;
			capacity[a][b] = capacity[b][a] = w;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		maxflow(0, 1);
		print_mincut();
		cout << '\n';
	}

	return 0;
}
