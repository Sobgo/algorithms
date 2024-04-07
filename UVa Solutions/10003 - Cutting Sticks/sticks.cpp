#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;
const int MAX_C = 50;

int case_num = 0;

vector<vector<int>> cache(MAX_C + 1, vector<int>(MAX_C + 1, -1));
vector<vector<int>> v(MAX_C + 1, vector<int>(MAX_C + 1, -1));

int get_cut_cost(int s, int e, int cs, int ce, vector<int> &c) {
	if (v[cs][ce] == case_num) return cache[cs][ce];

	v[cs][ce] = case_num;
	if (cs >= ce) return cache[cs][ce] = 0;

	int min_cost = INF;

	for (int i = cs; i < ce; ++i) {
		int cost = e - s + get_cut_cost(s, c[i], cs, i, c) + get_cut_cost(c[i], e, i + 1, ce, c);
		min_cost = min(min_cost, cost);
	}

	return cache[cs][ce] = min_cost;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int l, n;

	while (true) {
		cin >> l;
		if (l == 0) break;

		cin >> n;
		vector<int> c(n);

		for (int i = 0; i < n; ++i) {
			cin >> c[i];
		}

		case_num += 1;
		cout << "The minimum cutting is " << get_cut_cost(0, l, 0, n, c) << ".\n";
	}

	return 0;
}
