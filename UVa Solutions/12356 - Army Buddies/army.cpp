#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int s, b;

	while (cin >> s >> b) {
		if (s == 0 && b == 0) break;

		vector<int> left(s + 1), right(s + 1);

		for (int i = 1; i <= s; ++i) {
			left[i] = i - 1;
			right[i] = i + 1;
		}

		left[1] = -1;
		right[s] = -1;

		int l, r;
		for (int i = 0; i < b; ++i) {
			cin >> l >> r;

			if (left[l] == -1) {
				cout << "* ";
			} else {
				cout << left[l] << ' ';
				right[left[l]] = right[r];
			}

			if (right[r] == -1) {
				cout << "*\n";
			} else {
				cout << right[r] << '\n';
				left[right[r]] = left[l];
			}
		}

		cout << "-\n";
	}

	return 0;
}
