#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T, n;
	cin >> T;

	while (T--) {
		cin >> n;

		vector<string> v(n);
		vector<bool> ok(n, false);

		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}

		if (v.size() == 1) {
			cout << 0 << "\n";
			continue;
		}

		int pos = 0;
		int total = 0;
		bool end = false;

		unordered_map<string, int> m;

		while (!end) {
			end = true;
			m.clear();

			for (int i = 0; i < n; ++i) {
				if (!ok[i]) {
					m[v[i].substr(0, pos)] += 1;
					end = false;
				}
			}

			for (int i = 0; i < n; ++i) {
				if (!ok[i]) {
					if (m[v[i].substr(0, pos)] == 1) {
						total += pos;
						ok[i] = true;
					}
				}
			}

			pos++;
		}

		cout << total << "\n";
	}

	return 0;
}
