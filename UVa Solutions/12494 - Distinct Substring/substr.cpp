#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	string s;

	for (int i = 0; i < t; ++i) {
		cin >> s;

		string sub;
		vector<unordered_set<string>> vs(201);
		int total = 0;
		bool add;

		for (int j = 1; j <= s.size(); ++j) {
			for (int l = 0; l <= s.size() - j; ++l) {
				sub = s.substr(l, j);

				int len = sub.size();

				sub += sub;
				add = true;

				for (int k = 0; k < len; ++k) {
					if (vs[len].find(sub.substr(k, len)) != vs[len].end()) {
						add = false;
						break;
					}
				}

				if (add) {
					total++;
					vs[len].insert(sub.substr(0, len));
				}
			}
		}

		cout << total << "\n";
	}

	return 0;
}
