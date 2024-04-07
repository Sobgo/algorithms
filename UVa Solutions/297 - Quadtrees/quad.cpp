#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

typedef long long int lli;

tuple<lli, lli, lli> to_num(string &s1, string &s2, int idx1 = 0, int idx2 = 0, int depth = 5) {
	if (s1[idx1] == 'e' && s2[idx2] == 'e') return {0, idx1, idx2};
	if (s1[idx1] != 'p' && s2[idx2] != 'p') return {(lli)pow(4, depth), idx1, idx2};
	lli total = 0;

	bool s1p = s1[idx1] == 'p';
	bool s2p = s2[idx2] == 'p';
	bool f = s1[idx1] == 'f' || s2[idx2] == 'f';

	for (int i = 0; i < 4; ++i) {
		auto res = to_num(s1, s2, idx1 + s1p, idx2 + s2p, depth - 1);

		if (f)
			total += (lli)pow(4, depth - 1);
		else
			total += get<0>(res);

		if (s1p) idx1 = get<1>(res);
		if (s2p) idx2 = get<2>(res);
	}

	return {total, idx1, idx2};
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; ++tc) {
		string a, b;
		cin >> a >> b;

		cout << "There are " << get<0>(to_num(a, b)) << " black pixels.\n";
	}

	return 0;
}
