#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int diff(string &s1, string &s2) {
	int total = 0;
	
	for (int i = 0; i < s1.size(); ++i) {
		if (s1[i] != s2[i]) total++;
	}

	return total;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int m, n;

	while (cin >> n >> m) {
		vector < pair <int, string> > v(n-1, {0, ""});

		string orig; cin >> orig;

		for (int i = 0; i < n - 1; ++i) {
			cin >> v[i].second;
			v[i].first = diff(orig, v[i].second);

		}

		sort(v.begin(), v.end());

		cout << orig << "\n";
		for (int i = 0; i < v.size(); ++i) {
			cout << v[i].second << "\n";
		}
	}

	return 0;
}
