#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	int p, n;

	while (t--) {
		cin >> p >> n;

		vector<pair<int, int>> v(n);
		vector<int> ans(n);

		for (int i = 0; i < n; ++i) {
			cin >> v[i].first;
			v[i].second = -i;
		}

		sort(v.begin(), v.end(), greater<pair<int, int>>());

		for (int i = 0; i < n; ++i) {
			int idx = ans.size() - 1 - i;
			ans[-v[idx].second] = min(v[idx].first, p / (n - i));
			p -= ans[-v[idx].second];
		}

		if (p > 0) {
			cout << "IMPOSSIBLE\n";
		} else {
			for (int i = 0; i < n - 1; ++i) {
				cout << ans[i] << " ";
			}
			cout << ans[n - 1] << "\n";
		}
	}

	return 0;
}
