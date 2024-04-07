#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

#define to first
#define weight second

typedef tuple<int, int, int> edge;
typedef priority_queue<edge, vector<edge>, greater<edge>> pqe;

int N, M;
vector<vector<pair<int, int>>> ADJ;

// adds unvisited edges coming out of node to pq
// marks node as visited
void add_edges(int node, vector<bool> &visited, pqe &pq) {
	visited[node] = true;

	for (auto edge : ADJ[node]) {
		if (!visited[edge.to]) {
			pq.push({edge.weight, node, edge.to});
		}
	}
}

// this is lazy version of prim's algorithm as it can add
// edges to pq which at processing time will be "stale"
// (edge.to will be already visited)
vector<edge> find_mst() {
	// priority queue of edges where edge consists
	// of three integers: weight, from, to
	// edges are sorted by weight ascending
	pqe pq;

	// edges of mst
	vector<edge> edges;

	// visited nodes
	vector<bool> visited(N, false);

	// set 0 as initial node
	add_edges(0, visited, pq);

	// since mst is a tree, it has N - 1 edges
	const int mst_size = N - 1;

	while (!pq.empty() && edges.size() < mst_size) {
		edge e = pq.top();
		pq.pop();

		// if to node is already visited, skip ("stale" edge)
		if (visited[get<2>(e)]) continue;

		// add edge to mst
		edges.push_back(e);
		add_edges(get<2>(e), visited, pq);
	}

	// if mst is not found, return empty vector
	if (edges.size() < mst_size) return vector<edge>();
	return edges;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// N - number of nodes, M - number of edges
	cin >> N >> M;

	// read adjacency list
	ADJ.resize(N);

	int a, b, w;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> w;

		ADJ[a].push_back({b, w});
		ADJ[b].push_back({a, w});
	}

	// find mst
	vector<edge> mst = find_mst();

	if (mst.empty()) {
		cout << "No MST found\n";
	} else {
		int mst_w = 0;

		for (auto e : mst) {
			mst_w += get<0>(e);
			cout << get<1>(e) << " -> " << get<2>(e) << " w: " << get<0>(e) << "\n";
		}

		cout << "MST weight: " << mst_w << "\n";
	}

	return 0;
}
