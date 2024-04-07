#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix;

int N;
matrix A, B;

vector<int> random_vec(int n) {
	vector<int> v(n);

	for (int i = 0; i < n; ++i) {
		v[i] = rand() % 1000;
	}

	return v;
}

bool isPow() {
	// if A * (A * v) != B * v
	// then A^2 != B

	// after 50 tries for random vector v
	// we can assume with high probability that A^2 == B

	const int tries = 50;

	for (int i = 0; i < tries; ++i) {
		vector<int> v, Av(N), Bv(N), AAv(N);
		v = random_vec(N);

		// A * v; B * v;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				Av[i] += A[i][j] * v[j];
				Bv[i] += B[i][j] * v[j];
			}
		}

		// A * Av
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				AAv[i] += A[i][j] * Av[j];
			}
		}

		// check if A * (A * v) == B * v
		for (int i = 0; i < N; ++i) {
			if (AAv[i] != Bv[i]) {
				return false;
			}
		}
	}

	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	srand(time(NULL));

	while (cin >> N) {
		if (N == 0) break;
		A = matrix(N, vector<int>(N));
		B = matrix(N, vector<int>(N));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> A[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> B[i][j];
			}
		}

		cout << (isPow() ? "YES\n" : "NO\n");
	}

	return 0;
}
