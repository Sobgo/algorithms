#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void DFS(int node, vvi &adj, vi &path) {

	for (int to = 0; to < adj.size(); ++to) {
		while (adj[node][to]) {
			adj[node][to]--;
			adj[to][node]--;

			DFS(to, adj, path);
		}
	}

	path.push_back(node);
}

vi eulerian_cycle(int n, vvi &adj) {
	vi deg(adj.size());

	for (int from = 0; from < adj.size(); ++from) {
		for (int to = 0; to < adj.size(); ++to) {
			deg[from] += adj[from][to];
		}
	}

	int start = 0;

	for (int i = 0; i < adj.size(); ++i) {
		if (deg[i] % 2 == 1) return vi();
		if (deg[i] > 0) start = i;
	}

	vi path;
	DFS(start, adj, path);

	if (path.size() - 1 != n) return vi();
	return path;
}

vvi read_adj(int n, int m) {
	int a, b;
	vvi adj(n, vi(n, 0));

	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		a--;
		b--;
		adj[a][b]++;
		adj[b][a]++;
	}

	return adj;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int i = 1; i <= t; ++i) {
		int n;
		cin >> n;

		vvi adj = read_adj(50, n);
		vi path = eulerian_cycle(n, adj);

		cout << "Case #" << i << "\n";

		if (path.size() == 0) {
			cout << "some beads may be lost\n";
		} else {
			for (int i = 0; i < path.size() - 1; ++i) {
				cout << path[i] + 1 << " " << path[i + 1] + 1 << "\n";
			}
		}

		cout << "\n";
	}

	return 0;
}
