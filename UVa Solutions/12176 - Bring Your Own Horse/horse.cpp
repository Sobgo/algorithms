#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

typedef pair<int, int> pi;
typedef tuple<int, int, int> ti;

typedef vector<pi> vp;
typedef vector<vp> vvp;
typedef priority_queue<ti, vector<ti>, greater<ti>> pq;

vector<int> visited;
int N, R, Q;

int bfs(vvp &adj, int a, int b, int idx) {
	queue<int> q;
	vector<pi> parents(N, {-1, 0});

	q.push(a);
	visited[a] = idx;

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (pi edge : adj[node]) {
			if (visited[edge.second] != idx) {
				visited[edge.second] = idx;
				parents[edge.second] = {node, edge.first};
				q.push(edge.second);
			}
		}
	}

	int max_weight = 0;
	while (b != a) {
		max_weight = max(max_weight, parents[b].second);
		b = parents[b].first;
	}

	return max_weight;
}

void add_edges(int node, vvp &adj, pq &q) {
	visited[node] = 0;

	for (pi edge : adj[node]) {
		if (visited[edge.second] == -1) {
			q.push({edge.first, node, edge.second});
		}
	}
}

vvp find_mst(vvp &adj) {
	vvp res(N);
	pq q;

	add_edges(0, adj, q);

	int w, from, to;

	while (!q.empty()) {
		w = get<0>(q.top());
		from = get<1>(q.top());
		to = get<2>(q.top());
		q.pop();

		if (visited[to] != -1) continue;

		res[to].push_back({w, from});
		res[from].push_back({w, to});

		add_edges(to, adj, q);
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; ++tc) {
		cout << "Case " << tc << "\n";

		cin >> N >> R;
		vvp adj(N);

		int a, b, l;

		for (int i = 0; i < R; i++) {
			cin >> a >> b >> l;
			a--;
			b--;
			adj[a].push_back({l, b});
			adj[b].push_back({l, a});
		}

		visited = vector<int>(N, -1);

		vvp res = find_mst(adj);

		cin >> Q;
		for (int i = 1; i <= Q; ++i) {
			cin >> a >> b;
			a--;
			b--;
			cout << bfs(res, a, b, i) << "\n";
		}

		cout << "\n";
	}

	return 0;
}
