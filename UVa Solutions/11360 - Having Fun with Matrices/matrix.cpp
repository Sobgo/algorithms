#include <iostream>
#include <vector>
using namespace std;

int M, N, T;
vector<vector<int>> matrix;

bool transposition = false;

void swap_rows(int i, int j) {
	for (int k = 0; k < N; ++k) {
		swap(matrix[i][k], matrix[j][k]);
	}
}

void swap_cols(int i, int j) {
	for (int k = 0; k < N; ++k) {
		swap(matrix[k][i], matrix[k][j]);
	}
}

void increment() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			matrix[i][j] = (matrix[i][j] + 1) % 10;
		}
	}
}

void decrement() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			matrix[i][j] = (matrix[i][j] + 9) % 10;
		}
	}
}

void print() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (transposition) {
				cout << matrix[j][i];
			} else {
				cout << matrix[i][j];
			}
		}
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string cmd;
	char dig;

	cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		matrix = vector<vector<int>>(N, vector<int>(N, 0));

		transposition = false;

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; j++) {
				cin >> dig;
				matrix[i][j] = dig - '0';
			}
		}

		cin >> M;

		while (M--) {
			cin >> cmd;

			if (cmd == "row") {
				int i, j;
				cin >> i >> j;

				if (transposition) {
					swap_cols(i - 1, j - 1);
				} else {
					swap_rows(i - 1, j - 1);
				}
			} else if (cmd == "col") {
				int i, j;
				cin >> i >> j;

				if (transposition) {
					swap_rows(i - 1, j - 1);
				} else {
					swap_cols(i - 1, j - 1);
				}
			} else if (cmd == "inc") {
				increment();
			} else if (cmd == "dec") {
				decrement();
			} else if (cmd == "transpose") {
				transposition = !transposition;
			}
		}

		cout << "Case #" << tc << "\n";
		print();
		cout << "\n";
	}

	return 0;
}
