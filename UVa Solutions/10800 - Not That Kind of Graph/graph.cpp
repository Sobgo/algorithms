#include <iostream>
#include <vector>
using namespace std;

typedef long long int lli;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	lli n;
	cin >> n;

	for (lli i = 0; i < n; ++i) {
		string s;
		cin >> s;

		vector<string> v(s.size() * 2 + 2, string(s.size() + 2, ' '));

		int y = s.size() + 1;

		int max_y = y;
		int min_y = y;

		for (int j = 0; j < s.size(); ++j) {
			if (s[j] == 'R') {
				v[y][j + 1] = '/';
				y--;
				if (y < min_y) min_y = y;
			} else if (s[j] == 'F') {
				y++;
				v[y][j + 1] = '\\';
				if (y > max_y) max_y = y;
			} else {
				v[y][j + 1] = '_';
			}
		}

		// remove trailing spaces form each line
		for (int j = min_y; j <= max_y; ++j) {
			int k = v[j].size() - 1;
			while (k >= 0 && v[j][k] == ' ') {
				v[j].pop_back();
				k--;
			}
		}

		cout << "Case #" << i + 1 << ":\n";

		if (v[min_y].size() != 0) cout << "|" << v[min_y] << "\n";

		for (int j = min_y + 1; j <= max_y; ++j) {
			cout << "|" << v[j] << "\n";
		}

		cout << "+";
		for (int j = 0; j < s.size() + 2; ++j) {
			cout << "-";
		}

		cout << "\n\n";
	}
}
