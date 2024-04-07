#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, t = 1;

	while (cin >> n) {
		unordered_map<string, int> mp;
		vector<string> rm(n);
		string s;

		for (int i = 0; i < n; ++i) {
			cin >> s;
			rm[i] = s;
			mp[s] = i;
		}

		cin >> m;

		string a, b;
		vector<vector<int>> adj(n);
		vector<int> indeg(n, 0);

		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			adj[mp[a]].push_back(mp[b]);
			indeg[mp[b]] += 1;
		}

		cout << "Case #" << t++ << ": Dilbert should drink beverages in this order: ";
		for (int i = 0; i < n; ++i) {
			auto it = find(indeg.begin(), indeg.end(), 0);
			if (it == indeg.end()) break;

			int idx = it - indeg.begin();
			indeg[idx] = -1;

			for (int v : adj[idx]) {
				indeg[v] -= 1;
			}

			cout << rm[idx];
			if (i < n - 1) cout << " ";
		}
		cout << ".\n\n";
	}

	return 0;
}
