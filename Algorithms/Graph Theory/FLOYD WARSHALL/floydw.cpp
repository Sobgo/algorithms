#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

#define INF 2147483647 / 2

vvi ADJ;

pair<vvi, vvi> floydwarshall() {
	vvi dist = ADJ;
	vvi parents(ADJ.size(), vi(ADJ.size(), -1));

	for (int i = 0; i < ADJ.size(); ++i) {
		for (int j = 0; j < ADJ.size(); ++j) {
			if (ADJ[i][j] != INF) parents[i][j] = j;
		}
	}

	for (int k = 0; k < ADJ.size(); ++k) {
		for (int i = 0; i < ADJ.size(); ++i) {
			for (int j = 0; j < ADJ.size(); ++j) {
				if (dist[i][k] == INF || dist[k][j] == INF) continue;

				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					parents[i][j] = parents[i][k];
				}
			}
		}
	}

	// update nodes affected by negative cycles
	for (int k = 0; k < ADJ.size(); ++k) {
		for (int i = 0; i < ADJ.size(); ++i) {
			for (int j = 0; j < ADJ.size(); ++j) {
				if (dist[i][k] == INF || dist[k][j] == INF) continue;

				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = -INF;
					parents[i][j] = -1;
				}
			}
		}
	}

	return {dist, parents};
}

vi path(int start, int end) {
	pair<vvi, vvi> fw = floydwarshall();

	vvi dist = fw.first;
	vvi parents = fw.second;

	vi path;
	if (dist[start][end] == INF) return path;

	int curr = start;

	while (curr != end) {
		if (curr == -1) return vi();
		path.push_back(curr);
		curr = parents[curr][end];
	}

	if (curr == -1) return vi();

	path.push_back(end);
	return path;
}

void read_adj(int n, int m) {
	int from, to, weight;
	ADJ = vvi(n, vi(n, INF));

	for (int i = 0; i < n; ++i) ADJ[i][i] = 0;

	for (int i = 0; i < m; ++i) {
		cin >> from >> to >> weight;
		ADJ[from][to] = weight;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vvi dist = floydwarshall().first;

	cout << "Distances matrix:\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (dist[i][j] == INF)
				cout << "INF ";
			else if (dist[i][j] == -INF)
				cout << "-INF ";
			else
				cout << dist[i][j] << " ";
		}
		cout << "\n\n";
	}

	cout << "Path from 0 to 8:\n";
	vi p = path(0, 8);

	for (int i = 0; i < p.size(); ++i) {
		cout << p[i] << " ";
	}
	cout << "\n";

	return 0;
}
