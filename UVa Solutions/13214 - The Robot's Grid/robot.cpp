#include <iostream>
#include <vector>
using namespace std;

typedef long long int lli;

vector < vector <lli> > cache(26, vector <lli> (26, -1));

lli solve_rect(int n, int m) {
	if (cache[n][m] != -1) return cache[n][m];

	lli ans = 0;

	for (int i = 0; i < n; ++i) {
		ans += solve_rect(n - i, m - 1);
	}

	return cache[n][m] = ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < cache.size(); ++i) {
		cache[0][i] = 1;
		cache[1][i] = 1;

		cache[i][0] = 1;
		cache[i][1] = 1;
	}

	int t; cin >> t;

	for (int i = 0; i < t; ++i) {
		int n, m; cin >> n >> m;
		cout << solve_rect(n, m) << "\n";
	}

	return 0;
}
