#include <iostream>
#include <string>
using namespace std;

int min_per(string &s) {
	for (int i = 1; i <= s.size(); ++i) {
		string sub = s.substr(0, i);

		if (s.size() % sub.size() != 0) continue;

		bool ok;

		for (int j = 0; j < s.size(); j += sub.size()) {
			ok = true;

			for (int k = 0; k < sub.size(); ++k) {
				if (sub[k] != s[k + j]) {
					ok = false;
					break;
				}
			}

			if (!ok) break;
		}

		if (ok) return i;
	}

	return s.size();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;

	string s;

	while (T--) {
		cin >> s;
		cout << min_per(s) << "\n";
	}

	return 0;
}
