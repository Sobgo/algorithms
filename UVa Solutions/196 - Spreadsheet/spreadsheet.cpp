#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<string>> v;
vector<vector<bool>> evaluated;

int letterPos(string &s, int pos) {
	int idx = 0;

	for (int i = pos; i < s.size(); ++i) {
		if (!isalpha(s[i])) break;
		idx = idx * 26 + s[i] - 'A' + 1;
	}

	return idx - 1;
}

int numPos(string &s, int pos) {
	int idx = 0;

	for (int i = pos; i < s.size(); ++i) {
		if (s[i] == '+') break;
		if (!isdigit(s[i])) continue;
		idx = idx * 10 + s[i] - '0';
	}

	return idx - 1;
}

void evalCell(int i, int j) {
	if (evaluated[i][j]) return;

	int sum = 0, letter, num;
	int prev = 1;

	string &formula = v[i][j];

	for (int pos = 1; pos < formula.size(); ++pos) {
		if (formula[pos] == '+') {
			letter = letterPos(formula, prev);
			num = numPos(formula, prev + 1);

			if (!evaluated[num][letter]) {
				evalCell(num, letter);
			}

			sum += atoi(v[num][letter].c_str());
			prev = pos + 1;
		}
	}

	letter = letterPos(formula, prev);
	num = numPos(formula, prev + 1);

	if (!evaluated[num][letter]) {
		evalCell(num, letter);
	}

	sum += atoi(v[num][letter].c_str());
	v[i][j] = to_string(sum);
	evaluated[i][j] = true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 0; tc < t; ++tc) {
		int n, m;
		cin >> n >> m;

		v = vector<vector<string>>(m, vector<string>(n));
		evaluated = vector<vector<bool>>(m, vector<bool>(n, false));

		queue<pair<int, int>> q;
		string s;

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> s;

				if (s[0] == '=') {
					q.push({i, j});
				} else {
					evaluated[i][j] = true;
				}
				v[i][j] = s;
			}
		}

		while (!q.empty()) {
			evalCell(q.front().first, q.front().second);
			q.pop();
		}

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n - 1; ++j) {
				cout << v[i][j] << ' ';
			}

			cout << v[i][n - 1] << '\n';
		}
	}

	return 0;
}
