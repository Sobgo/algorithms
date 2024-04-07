#include <iostream>
#include <vector>
using namespace std;

typedef long long int lli;
const lli MOD = 1000000009;
const int MAX = 513;

lli case_num;

vector<vector<lli>> nCr(MAX, vector<lli>(MAX, 0));
vector<vector<lli>> cache(MAX, vector<lli>(MAX, 0));
vector<vector<int>> v(MAX, vector<int>(MAX, -1));

lli dp(int spots, int nodes, int &limit) {
	if (spots == 0) return nodes == 0;
	if (v[spots][nodes] == case_num) return cache[spots][nodes];
	v[spots][nodes] = case_num;

	lli result = 0;

	for (int i = 0; i <= min(limit, nodes); ++i) {
		result = (result + (nCr[nodes][i] * dp(spots - 1, nodes - i, limit)) % MOD) % MOD;
	}

	return cache[spots][nodes] = result;
}

lli get_all_trees(int d, int k, vector<int> &c) {
	lli ans = 1;

	for (int i = 1; i <= d; ++i) {
		if (c[i - 1] * k < c[i]) return 0;
		ans = (ans * dp(c[i - 1], c[i], k)) % MOD;
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	nCr[0][0] = 1;

	for (int i = 1; i < nCr.size(); ++i) {
		nCr[i][0] = 1;

		for (int j = 1; j <= i; ++j) {
			nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % MOD;
		}
	}

	int t, d, k;
	cin >> t;

	for (case_num = 1; case_num <= t; ++case_num) {
		cin >> d >> k;

		vector<int> c(d + 1);

		for (int j = 0; j <= d; ++j) {
			cin >> c[j];
		}

		cout << "Case " << case_num << ": " << get_all_trees(d, k, c) << "\n";
	}

	return 0;
}
