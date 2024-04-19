#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using pi = pair<int, int>;
using vi = vector<int>;
using vp = vector<pi>;

const int INF = 1e9;

int N, M;
vector<vector<pi>> ADJ;

#define to first
#define w second

vi dijkstra(int start) {
	priority_queue<pi, vp, greater<pi>> pq;
	vi dist(N, INF);

	dist[start] = 0;
	pq.push({0, start});

	while (!pq.empty()) {
		int weight = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		if (dist[node] < weight) continue;

		for (pi next : ADJ[node]) {
			if (dist[next.to] > dist[node] + next.w) {
				dist[next.to] = dist[node] + next.w;
				pq.push({dist[next.to], next.to});
			}
		}
	}

	return dist;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int tc;
	cin >> tc;
	int t, e;

	while (tc-- > 0) {
		cin >> N >> e >> t >> M;

		ADJ = vector<vector<pi>>(N);

		for (int i = 0; i < M; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			--u;
			--v;
			ADJ[v].push_back({u, w});
		}

		vi dist = dijkstra(--e);

		int ans = 0;
		for (int d : dist) {
			if (d <= t) ++ans;
		}

		cout << ans << '\n';
		if (tc > 0) cout << '\n';
	}

	return 0;
}
