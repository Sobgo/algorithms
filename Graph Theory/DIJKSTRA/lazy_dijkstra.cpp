#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 2147483647

#define weight first
#define to second

int N, M;
// adjacency list (weight, node) pairs
vector < vector < pair <int, int> > > ADJ; 

// returns the distance from start to all other nodes
// and the parent array (previous node in path from each node)
pair < vector <int>, vector <int> > dijkstra(int start) {
	// priority queue of pairs (distance, node)
	// where distance is total weight of path used to reach node
	priority_queue < pair <int, int> > pq;

	// distance from start to all other nodes, initially INF,
	// during algorithm will store current best distance
	vector <int> dist(N, INF);

	// for path reconstruction
	vector <int> parent(N, -1);

	// set start as initial node
	dist[start] = 0;
	pq.push({0, start});

	while (!pq.empty()) {
		pair <int, int> cur = pq.top();
		pq.pop();

		// if we already found a better path to this node ignore it
		if (dist[cur.to] < cur.weight) continue;

		// update distances to all nodes that this path improves distance to
		for (pair <int, int> next : ADJ[cur.to]) {	
			if (dist[next.to] > dist[cur.to] + next.weight) {
				dist[next.to] = dist[cur.to] + next.weight;
				
				pq.push({dist[next.to], next.to});
				parent[next.to] = cur.to;
			}
		}
	}

	return {dist, parent};
}

// finds shortest path from start to end
vector <int> path(int start, int end) {
	pair < vector <int>, vector <int> > res = dijkstra(start);
	vector <int> dist = res.first;
	vector <int> parent = res.second;

	// no path
	if(dist[end] == INF) return vector <int>();

	// reconstruct path from end to start
	vector <int> path;
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

	// read adjacency list
	ADJ.resize(N);

	int a, b, w;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> w;
		ADJ[a].push_back({w, b});
		//ADJ[b].push_back({w, a});
	}

	// find shortest path from start to end
	int start, end;
	cin >> start >> end;
	
	vector <int> res = path(start, end);

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
