#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int n;
vector<vector<double>> adj;
vector<pair<double, double>> pos;

vector<int> solve_brute(const int start) {
	vector<int> res;

	for (int i = 0; i < n; ++i) {
		res.push_back(i);
	}

	vector<int> best_path = res;
	double best_dist = INFINITY;

	while (next_permutation(res.begin(), res.end())) {
		double dist = 0.0;

		for (int i = 1; i < res.size(); ++i) {
			dist += adj[res[i - 1]][res[i]];
		}

		if (dist < best_dist) {
			best_dist = dist;
			best_path = res;
		}
	}

	return best_path;
}

double get_distance(int a, int b) {
	return sqrt(pow(pos[a].first - pos[b].first, 2) + pow(pos[a].second - pos[b].second, 2));
}

void setup_matrix(const int &start) {
	pos.assign(n, pair<double, double>());

	for (int i = 0; i < n; ++i) {
		cin >> pos[i].first >> pos[i].second;
	}

	adj.assign(n, vector<double>(n));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			adj[i][j] = adj[j][i] = get_distance(i, j) + 16.0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int iter = 0;
	const int start = 0;

	while (true) {
		cin >> n;
		if (n == 0) break;

		setup_matrix(start);
		vector<int> opt_path = solve_brute(start);
		double opt_cost = 0.0;

		cout << "**********************************************************\n";
		cout << "Network #" << ++iter << '\n';

		for (int i = 0; i < opt_path.size() - 1; ++i) {
			cout << "Cable requirement to connect";
			cout << " (" << pos[opt_path[i]].first << "," << pos[opt_path[i]].second << ")";
			cout << " to ";
			cout << "(" << pos[opt_path[i + 1]].first << "," << pos[opt_path[i + 1]].second << ")";
			cout << " is ";
			cout << fixed << setprecision(2);
			cout << adj[opt_path[i]][opt_path[i + 1]] << " feet.\n";
			opt_cost += adj[opt_path[i]][opt_path[i + 1]];
			cout << setprecision(0);
		}

		cout << fixed << setprecision(2);
		cout << "Number of feet of cable required is " << opt_cost << ".\n";
		cout << setprecision(0);
	}

	return 0;
}
