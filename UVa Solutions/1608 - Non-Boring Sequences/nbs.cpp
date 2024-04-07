#include <array>
#include <iostream>
#include <unordered_map>
using namespace std;

typedef unsigned int uint;

array<uint, 200002> V, L, R;
unordered_map<uint, uint> M;

// checking order here is important
bool eval(int s, int e) {
	if (e <= s) return true;

	uint l = s, r = e;

	while (l <= r) {
		if (R[l] > e && L[l] < s) {
			return eval(s, l - 1) && eval(l + 1, e);
		}

		if (R[r] > e && L[r] < s) {
			return eval(s, r - 1) && eval(r + 1, e);
		}

		l++;
		r--;
	}

	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, n;
	cin >> t;

	while (t--) {
		cin >> n;
		M.clear();

		for (int i = 1; i <= n; ++i) {
			cin >> V[i];
			L[i] = 1;
			R[i] = n + 1;
		}

		for (int i = 1; i <= n; ++i) {
			L[i] = M[V[i]];
			R[L[i]] = i;
			M[V[i]] = i;
		}

		cout << (eval(1, n) ? "non-boring" : "boring") << '\n';
	}

	return 0;
}
