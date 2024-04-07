#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s;
	bool skip = true;

	while (true) {
		skip = true;
		cin >> s;
		if (s == "#") return 0;

		if (s.size() == 0) {
			cout << "";
			continue;
		}

		vector<char> a(27, 0);
		string ans;
		sort(s.begin(), s.end(), greater<char>());

		char prev = s[0];

		for (char c : s) {
			if (prev != c) {
				if (a[prev - 'a'] % 2 != 0) {
					if (!skip) {
						ans.push_back(prev);
					} else {
						skip = false;
					}
				}
			}

			a[c - 'a']++;
			prev = c;
		}

		if (a[prev - 'a'] % 2 != 0) {
			if (!skip) {
				ans.push_back(prev);
			}
		}

		reverse(ans.begin(), ans.end());

		cout << ans << "\n";
	}

	return 0;
}
