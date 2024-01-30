#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;

#define x first
#define y second

#define TSPLIB 1
const int MAX_TIME_SEC = 60 * 5;

typedef long long int lli;
typedef vector < pair <int, int> > vp;
typedef vector <int> vi;

int N;
vp points;

int EUC_2D_sq(pair <int, int> &a, pair <int, int> &b) {
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

lli path_len(vi &path) {
	lli len = 0;
	for (int i = 0; i < path.size()-1; ++i) {
		len += (lli)(sqrt(EUC_2D_sq(points[path[i]], points[path[i+1]])) + 0.5);
	}
	len += (lli)(sqrt(EUC_2D_sq(points[path[0]], points[path[path.size()-1]])) + 0.5);

	return len;
}

vi nearest_neighbor();
bool two_opt_swap(vi &path, int i, int j);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// step 0: read input (in TSPLIB format)
	string name, s;

	while (cin >> s) {
		if (s == "NAME") {
			cin >> s >> name;
		} else if (s == "DIMENSION") {
			cin >> s >> N;
		} else if (s == "NODE_COORD_SECTION") {
			break;
		}
	}

	points = vp(N);

	int idx;
	for (int i = 0; i < N; ++i) {
		cin >> idx;
		cin >> points[i].x >> points[i].y;
	}

	// step 1: generate initial path
	// with greedy algorithm

	vi path = nearest_neighbor();

	int prev_time = -1, time = (double)clock()/CLOCKS_PER_SEC;
	lli len = path_len(path);

	#if !TSPLIB

	cout << len << ", " << time << ": ";

	for (int k = 0; k < N - 1; ++k) {
		cout << path[k] << "->";
	}
	cout << path[N-1] << "\n";

	#endif

	// step 2: improve path by local search
	
	if (time < MAX_TIME_SEC) {
		bool improved = true;
		int per = N/100;
		int passes = 0;

		while (improved) {
			improved = false;
			++passes;

			for (int i = 0; i < N-1; ++i) {

				prev_time = time;
				time = (double)clock()/CLOCKS_PER_SEC;

				#if TSPLIB

				// clear console
				cerr << "\033[2J\033[1;1H";

				cerr << min(i/per, 100) << "% of search space explored (pass: " << passes << ")\n";
				cerr << "Time elapsed: " << time << "s\n";
				cerr << "Best so far: " << ((time != prev_time) ? (len = path_len(path)) : len) << "\n\n";

				if (time > MAX_TIME_SEC) {

					cerr << "Time limit exceeded\n";
					cerr << "Terminating...\n\n";

					improved = false;
					break;
				}

				#else

				// to prevent > GB output
				if (i % 10000 == 0) {
					cout << path_len(path) << ", " << time << ": ";

					for (int k = 0; k < N - 1; ++k) {
						cout << path[k] << "->";
					}
					cout << path[N-1] << "\n";
				}

				#endif

				for (int j = i+1; j < N; ++j) {
					improved |= two_opt_swap(path, i, j);
				}
			}
		}
	}

	// step 3: print path

	#if TSPLIB

	len = path_len(path);
	cerr << "Best tour found: " << len << "\n\n";

	cout << "NAME : " << name << "\n";
	cout << "COMMENT : " << len << "\n";
	cout << "TYPE : TOUR\n";
	cout << "DIMENSION : " << N << "\n";
	cout << "TOUR_SECTION\n";

	for (int i = 0; i < N; ++i) {
		cout << path[i] + 1 << "\n";
	}

	cout << "-1\n";
	cout << "EOF\n";

	#else

	time = (double)clock()/CLOCKS_PER_SEC;

	cout << path_len(path) << ", " << time << ": ";

	for (int k = 0; k < N - 1; ++k) {
		cout << path[k] << "->";
	}
	cout << path[N-1] << "\n";

	#endif

	return 0;
}

vi nearest_neighbor() {
	vi path(N);
	vector <bool> visited(N, false);

	visited[0] = true;
	path[0] = 0;

	for (int i = 1; i < N; ++i) {
		int best = -1;
		int best_dist = 1e9;

		#if TSPLIB

		int time = (double)clock()/CLOCKS_PER_SEC;

		// clear console
		cerr << "\033[2J\033[1;1H";
		
		cerr << "Generating initial tour...\n";
		cerr << "Time elapsed: " << time << "s\n";
		cerr << "Progress: " << i << "/" << N << "\n\n";

		if (time > MAX_TIME_SEC) {
			cerr << "Time limit exceeded\n";
			cerr << "Terminating...\n\n";
			break;
		}

		#endif

		for (int j = 0; j < N; ++j) {
			if (!visited[j] && EUC_2D_sq(points[path[i-1]], points[j]) < best_dist) {
				best_dist = EUC_2D_sq(points[path[i-1]], points[j]);
				best = j;
			}
		}

		visited[best] = true;
		path[i] = best;
	}

	// add remaining vertices to path (if time limit exceeded)
	for (int i = 0; i < N; ++i) {
		if (!visited[i]) {
			path.push_back(i);
		}
	}

	return path;
}

bool two_opt_swap(vi &path, int i, int j) {
	int delta = EUC_2D_sq(points[path[i]], points[path[j]])
				+ EUC_2D_sq(points[path[(i+1) % N]], points[path[(j+1) % N]])
				- EUC_2D_sq(points[path[i]], points[path[(i+1) % N]])
				- EUC_2D_sq(points[path[j]], points[path[(j+1) % N]]);

	if (delta < 0) {
		reverse(path.begin() + i + 1, path.begin() + j + 1);
		return true;
	}

	return false;
}
