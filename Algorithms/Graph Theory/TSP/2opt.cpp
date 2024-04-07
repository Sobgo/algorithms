#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

const int ITER = 1000;

#define x first
#define y second

typedef long long int lli;
typedef vector<pair<lli, lli>> vp;

lli N;
vp points;

lli EUC_2D_sq(pair<lli, lli> a, pair<lli, lli> b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

lli path_len_sq(vector<int> &path) {
	lli len = 0;
	for (int i = 0; i < path.size() - 1; ++i) {
		len += EUC_2D_sq(points[path[i]], points[path[i + 1]]);
	}
	return len;
}

lli path_len(vector<int> &path) {
	lli len = 0;
	for (int i = 0; i < path.size() - 1; ++i) {
		len += (lli)(sqrt(EUC_2D_sq(points[path[i]], points[path[i + 1]])) + 0.5);
	}
	return len;
}

// try to improve path by 2-opt
vector<int> improve(vector<int> &path) {
	lli cur_len = path_len_sq(path);
	bool improved = true;

	while (improved) {
		improved = false;

		for (int i = 0; i < N - 1; ++i) {
			for (int j = i + 1; j < N; ++j) {

				// clang-format off
				lli delta = EUC_2D_sq(points[path[i]], points[path[j]])
						  + EUC_2D_sq(points[path[(i+1) % N]], points[path[(j+1) % N]])
						  - EUC_2D_sq(points[path[i]], points[path[(i+1) % N]])
						  - EUC_2D_sq(points[path[j]], points[path[(j+1) % N]]);
				// clang-format on

				if (delta < 0) {
					improved = true;
					reverse(path.begin() + i + 1, path.begin() + j + 1);
					cur_len += delta;
				}
			}
		}
	}

	return path;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	points = vp(N);

	lli idx;
	for (int i = 0; i < N; ++i) {
		cin >> idx;
		cin >> points[i].x >> points[i].y;
	}

	vector<int> best_path;
	lli best_len = 1e18;

	for (int i = 0; i < ITER; ++i) {
		// random permutation as initial path
		vector<int> path(N);
		for (int i = 0; i < N; ++i) path[i] = i;
		shuffle(path.begin(), path.end(), mt19937(random_device()()));

		path = improve(path);

		lli cur_len = path_len_sq(path);
		if (cur_len < best_len) {
			best_len = cur_len;
			best_path = path;
		}
	}

	cout << path_len(best_path) << "\n\n";

	for (int i = 0; i < N; ++i) {
		cout << best_path[i] << "\n";
	}

	return 0;
}
