#include <iostream>
using namespace std;

long long int gcd(long long int a, long long int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long int t, c;
	cin >> t;

	while (t--) {
		cin >> c;

		long long int n, g = 0, m = 0;

		for (int i = 0; i < c; ++i) {
			long long int total = 0;

			for (int j = 0; j < 9; ++j) {
				cin >> n;
				total += n;
			}

			cin >> n;

			total -= n;
			m = max(m, n);
			g = (i == 0) ? total : gcd(g, total);
		}

		if (m < g && g > 1) cout << g << "\n";
		else cout << "impossible\n";
	}

	return 0;
}
