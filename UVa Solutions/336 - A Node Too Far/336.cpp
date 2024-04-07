#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

int BFS(int start, vvi &adj, vb &visited, int max_depth) {
	queue<pair<int, int>> q;
	int node, depth, total = 1;

	q.push({start, 0});
	visited[start] = true;

	while (!q.empty()) {
		node = q.front().first;
		depth = q.front().second;
		q.pop();

		for (auto next : adj[node]) {
			if (!visited[next] && depth + 1 <= max_depth) {
				visited[next] = true;
				q.push({next, depth + 1});
				total++;
			}
		}
	}

	return total;
}

int read_adj(int n, int m, vvi &adj, map<int, int> &mp, vector<int> &mp2) {
	int a, b, iter = 0;

	for (int i = 0; i < m; ++i) {
		cin >> a >> b;

		if (mp.find(a) == mp.end()) {
			mp.insert({a, iter});
			mp2[iter] = a;
			iter++;
		}

		if (mp.find(b) == mp.end()) {
			mp.insert({b, iter});
			mp2[iter] = b;
			iter++;
		}

		adj[mp[a]].push_back(mp[b]);
		adj[mp[b]].push_back(mp[a]);
	}

	return iter;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, iter = 1;

	while (true) {
		n = 30;
		map<int, int> mp;
		vector<int> mp2(n);
		vvi adj(n);
		vb visited;

		cin >> m;
		if (m == 0) break;

		n = read_adj(n, m, adj, mp, mp2);
		int start, max_depth;

		while (true) {
			cin >> start >> max_depth;
			if (start == 0 && max_depth == 0) break;

			visited.assign(n, false);

			if (mp.find(start) == mp.end()) {
				cout << "Case " << iter++ << ": ";
				cout << n << " nodes not reachable from node " << start << " with TTL = " << max_depth << ".\n";
				continue;
			}

			int total = BFS(mp[start], adj, visited, max_depth);

			cout << "Case " << iter++ << ": ";
			cout << n - total << " nodes not reachable from node " << start << " with TTL = " << max_depth << ".\n";
		}
	}

	return 0;
}
