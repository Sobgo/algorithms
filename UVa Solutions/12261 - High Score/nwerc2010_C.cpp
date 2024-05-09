#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	string s;

	while (n--) {
		cin >> s;

		int mini = 1e9;

		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == 'A') continue;

			// try right

			int shift = 0;
			int count = min((int)s.size() - i, i);

			for (int j = 0; j < s.size(); ++j) {
				int idx = (i + j + s.size()) % s.size();

				if (s[idx] != 'A') {
					count += shift + min(s[idx] - 'A', 'Z' - s[idx] + 1);
					shift = 0;
				}

				shift += 1;
			}

			if (count < mini) mini = count;

			// try left

			shift = 0;
			count = min((int)s.size() - i, i);

			for (int j = 0; j < s.size(); ++j) {
				int idx = (i - j + s.size()) % s.size();

				if (s[idx] != 'A') {
					count += shift + min(s[idx] - 'A', 'Z' - s[idx] + 1);
					shift = 0;
				}

				shift += 1;
			}

			if (count < mini) mini = count;
		}

		cout << (mini == 1e9 ? 0 : mini) << '\n';
	}

	return 0;
}
