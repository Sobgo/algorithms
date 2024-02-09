#include <iostream>
#include <vector>
using namespace std;

typedef vector <bool> vb;
typedef vector < vector <char> > vvc;

void DFS(int i, int j, vvc &adj) {
	if (adj[i][j] == '*') return;
	adj[i][j] = '*';

	for (int k = -1; k <= 1; ++k) {
		for (int l = -1; l <= 1; ++l) {
			DFS(i + k, j + l, adj);
		}
	}
}

vvc read_adj(int n, int m) {
	vvc adj(n+2, vector <char> (m+2, '*'));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; j++) {
			cin >> adj[i][j];
		}
	}

	return adj;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, t = 1;
	while(cin >> n >> m) {
		if (n == 0 && m == 0) break;

		vvc adj = read_adj(n, m);

		int total = 0;

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; j++) {
				if (adj[i][j] == '@') {
					total++;
					DFS(i, j, adj);
				}
			}
		}

		cout << total << "\n";
	}

	return 0;
}
