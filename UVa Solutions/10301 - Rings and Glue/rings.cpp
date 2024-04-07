#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef pair<double, double> pdd;

double get_dis(pdd &a, pdd &b) {
	return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

int DFS(int node, vvi &adj, vb &visited) {
	if (visited[node]) return 0;
	visited[node] = true;

	int total = 1;

	for (auto next : adj[node]) {
		total += DFS(next, adj, visited);
	}

	return total;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;

	while (true) {
		cin >> n;
		if (n < 0) return 0;

		vector<pdd> cords(n);
		vector<double> rad(n);

		for (int i = 0; i < n; ++i) {
			cin >> cords[i].first >> cords[i].second >> rad[i];
		}

		vvi adj(n);
		vector<bool> visited(n);

		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (
					abs(rad[i] - rad[j]) < get_dis(cords[i], cords[j]) && get_dis(cords[i], cords[j]) < rad[i] + rad[j]) {
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}

		int max_val = 0;

		for (int i = 0; i < n; ++i) {
			if (!visited[i]) {
				max_val = max(max_val, DFS(i, adj, visited));
			}
		}

		cout << "The largest component contains " << max_val << " ring" << (max_val == 1 ? "" : "s") << ".\n";
	}

	return 0;
}
