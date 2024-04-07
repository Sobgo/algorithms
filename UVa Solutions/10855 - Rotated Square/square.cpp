#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> matrix;

bool comp(matrix &key, matrix &img, int i, int j) {
	for (int k = 0; k < key.size(); ++k) {
		for (int l = 0; l < key.size(); ++l) {
			if (key[k][l] != img[i + k][j + l]) {
				return false;
			}
		}
	}

	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;

		matrix img(n, vector<char>(n));
		vector<matrix> keys(4, matrix(m, vector<char>(m)));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> img[i][j];
			}
		}

		char val;

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				cin >> val;

				keys[0][i][j] = val;
				keys[1][j][m - i - 1] = val;
				keys[2][m - i - 1][m - j - 1] = val;
				keys[3][m - j - 1][i] = val;
			}
		}

		for (int k = 0; k < 4; ++k) {
			int total = 0;

			for (int i = 0; i <= n - m; ++i) {
				for (int j = 0; j <= n - m; ++j) {
					total += comp(keys[k], img, i, j);
				}
			}

			cout << total;
			if (k < 3) cout << ' ';
		}

		cout << '\n';
	}

	return 0;
}
