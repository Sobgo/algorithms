#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vp;
typedef vector<vp> vvp;

#define to first
#define w second

#define INF 2147483647

int N, M;
vvp ADJ;

pair<vi, vi> dijkstra(int start) {
	priority_queue<pi, vp, greater<pi>> pq;
	vector<int> dist(N, INF);
	vector<int> parent(N, -1);

	dist[start] = 0;
	pq.push({0, start});

	while (!pq.empty()) {
		int weight = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		// if we already found a better path to this node ignore it
		if (dist[node] < weight) continue;

		// update distances to all nodes that this path improves distance to
		for (pi next : ADJ[node]) {
			if (dist[next.to] > dist[node] + next.w) {
				dist[next.to] = dist[node] + next.w;
				pq.push({dist[next.to], next.to});
				parent[next.to] = node;
			}
		}
	}

	return {dist, parent};
}

vector<int> path(int start, int end) {
	pair<vi, vi> res = dijkstra(start);
	vi dist = res.first;
	vi parent = res.second;

	// no path
	if (dist[end] == INF) return vector<int>();

	// reconstruct path from end to start
	vi path;
	for (int at = end; at != -1; at = parent[at]) {
		path.push_back(at);
	}

	// and reverse it
	reverse(path.begin(), path.end());

	return path;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// N = number of nodes, M = number of edges
	cin >> N >> M;
	ADJ = vvp(N);

	int a, b, weight;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> weight;
		ADJ[a].push_back({b, weight});
		// ADJ[b].push_back({a, weight});
	}

	int start, end;
	cin >> start >> end;

	vi res = path(start, end);

	if (res.empty()) {
		cout << "No path\n";
	} else {
		cout << "Shortest path: ";
		for (int node : res) {
			cout << node << " ";
		}
		cout << '\n';
	}

	return 0;
}
