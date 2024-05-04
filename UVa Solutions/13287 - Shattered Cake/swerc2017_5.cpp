#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int w, n;

	while (cin >> w >> n) {
		int area = 0;

		for (int i = 0; i < n; ++i) {
			int wi, li;
			cin >> wi >> li;
			area += wi * li;
		}

		cout << area / w << "\n";
	}

	return 0;
}
