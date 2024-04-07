#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int from, to, weight;
};

typedef vector<edge> ve;
typedef vector<int> vi;

#define INF 2147483647 / 2

vi bf(int start, ve &edges, int n) {
	vi dist(n, INF);
	dist[start] = 0;

	for (int i = 0; i < n - 1; ++i) {
		cout << "";
		for (auto edge : edges) {
			if (dist[edge.from] == INF) continue;
			if (dist[edge.from] + edge.weight < dist[edge.to]) {
				dist[edge.to] = dist[edge.from] + edge.weight;
			}
		}
	}

	// update nodes affected by negative cycles
	for (int i = 0; i < n - 1; ++i) {
		for (auto edge : edges) {
			if (dist[edge.from] + edge.weight < dist[edge.to]) {
				dist[edge.to] = -INF;
			}
		}
	}

	return dist;
}

ve read_edges(int m) {
	int from, to, weight;
	ve edges(m);

	for (int i = 0; i < m; ++i) {
		cin >> from >> to >> weight;
		edges[i] = {from, to, weight};
	}

	return edges;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	ve edges = read_edges(m);
	int start;
	cin >> start;

	vi dist = bf(start, edges, n);

	cout << "Distances from " << start << ":\n";
	for (int i = 0; i < dist.size(); ++i) {
		cout << i << ": ";
		if (dist[i] == INF)
			cout << "INF\n";
		else if (dist[i] == -INF)
			cout << "-INF\n";
		else
			cout << dist[i] << "\n";
	}

	return 0;
}
