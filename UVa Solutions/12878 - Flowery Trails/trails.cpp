#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long int lli;
typedef pair<int, int> pi;
typedef vector<pi> vp;
typedef vector<vp> vvp;

#define INF 2147483647

int P, T;
vvp ADJ;

vvp dijkstra(int s, int e) {
	vector<int> dist(P, INF);
	vvp parents(P);
	priority_queue<pi, vp, greater<pi>> pq;
	int node, weight;

	dist[s] = 0;
	pq.push({0, s});

	while (!pq.empty()) {
		weight = pq.top().first;
		node = pq.top().second;
		pq.pop();

		if (dist[node] < weight) continue;

		for (pi next : ADJ[node]) {
			if (dist[node] + next.second < dist[next.first]) {
				dist[next.first] = dist[node] + next.second;
				pq.push({dist[next.first], next.first});

				parents[next.first].clear();
				parents[next.first].push_back({node, next.second});
			} else if (dist[node] + next.second == dist[next.first]) {
				parents[next.first].push_back({node, next.second});
			}
		}
	}

	return parents;
}

lli path_len(vvp &parents, int s, int e) {
	vector<bool> visited(P, false);
	queue<int> q;

	lli len = 0;

	q.push(e);
	visited[e] = true;

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (pi parent : parents[node]) {
			if (!visited[parent.first]) {
				q.push(parent.first);
				visited[parent.first] = true;
			}
			len += parent.second;
		}
	}

	return len;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> P >> T) {
		ADJ = vvp(P);

		int p1, p2, l;
		for (int i = 0; i < T; ++i) {
			cin >> p1 >> p2 >> l;
			ADJ[p1].push_back({p2, l});
			ADJ[p2].push_back({p1, l});
		}

		vvp parents = dijkstra(0, P - 1);
		cout << path_len(parents, 0, P - 1) * 2 << '\n';
	}

	return 0;
}
