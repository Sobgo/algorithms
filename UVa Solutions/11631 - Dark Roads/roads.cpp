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

void add_edges(int node, vector<bool> &visited, pqe &pq) {
	visited[node] = true;

	for (auto edge : ADJ[node]) {
		if (!visited[edge.to]) {
			pq.push({edge.weight, node, edge.to});
		}
	}
}

vector<edge> find_mst() {
	pqe pq;
	vector<edge> edges;
	vector<bool> visited(N);

	add_edges(0, visited, pq);

	const int mst_size = N - 1;

	while (!pq.empty() && edges.size() < mst_size) {
		edge e = pq.top();
		pq.pop();

		if (visited[get<2>(e)]) continue;

		edges.push_back(e);
		add_edges(get<2>(e), visited, pq);
	}

	if (edges.size() < mst_size) return vector<edge>();
	return edges;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> N >> M) {
		if (N == 0 && M == 0) break;

		ADJ = vector<vector<pair<int, int>>>(N);

		int total_w = 0;

		int a, b, w;
		for (int i = 0; i < M; ++i) {
			cin >> a >> b >> w;

			ADJ[a].push_back({b, w});
			ADJ[b].push_back({a, w});
			total_w += w;
		}

		vector<edge> mst = find_mst();

		int mst_w = 0;

		for (auto e : mst) {
			mst_w += get<0>(e);
		}

		cout << total_w - mst_w << "\n";
	}
}
