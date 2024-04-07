#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void print(int l, int r, int m) {
	if (l > r || m < 0) return;

	// assume that right tree is full
	int parent = r - pow(2, m) + 1;

	if (parent < l) {
		// right tree is not full => left tree is empty
		cout << " " << l;
		print(l + 1, r, m - 1);
	} else {
		// divide on parent and process left subtree then right
		cout << " " << parent;
		print(l, parent - 1, m - 1);
		print(parent + 1, r, m - 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, t = 1;

	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;

		cout << "Case " << t++ << ":";

		if (pow(2, m) - 1 < n) {
			cout << " Impossible.\n";
			continue;
		}

		print(1, n, m - 1);
		cout << '\n';
	}

	return 0;
}
