#include <iostream>
#include <vector>
using namespace std;

typedef vector <int> v1i;
typedef vector <v1i> v2i;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;
	string s;

	for (int tc = 1; tc <= t; ++tc) {
		cin >> s;

		v2i lookup(s.size()+1, v1i(26, -1));

		for (int i = s.size() - 1; i >= 0; --i) {
			lookup[i] = lookup[i + 1];
			lookup[i][s[i] - 'A'] = i;
		}

		int total = 0;

		for (int i = 0; i < 26; ++i) {
			if (lookup[0][i] == -1) continue;
			int x = lookup[0][i] + 1;

			for (int j = 0; j < 26; ++j) {
				if(lookup[x][j] == -1) continue;
				int y = lookup[x][j] + 1;
				
				for (int k = 0; k < 26; ++k) {
					if (lookup[y][k] == -1) continue;
					total++;
				}
			}
		}

		cout << total << "\n";
	}

	return 0;
}
