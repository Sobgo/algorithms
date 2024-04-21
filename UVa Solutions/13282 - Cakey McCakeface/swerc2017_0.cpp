#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;

	while (cin >> n >> m) {
		vector<int> in(n, 0);
		vector<int> out(m, 0);
		vector<int> diff;

		for (int i = 0; i < n; ++i) {
			cin >> in[i];
		}

		for (int i = 0; i < m; ++i) {
			cin >> out[i];
		}

		int prev = 0;

		for (int i = 0; i < n; ++i) {
			for (int j = prev; j < m; ++j) {
				if (in[i] <= out[j]) {
					prev = j;
					break;
				}
			}

			if (in[i] > out[prev]) continue;

			for (int j = prev; j < m; ++j) {
				diff.push_back(out[j] - in[i]);
			}
		}

		sort(diff.begin(), diff.end());

		int max = 0, max_count = 0;
		int cur, count = 0;

		for (int i = 0; i < diff.size(); ++i) {
			if (diff[i] == cur) {
				++count;
			} else {
				if (count > max_count) {
					max_count = count;
					max = cur;
				}

				cur = diff[i];
				count = 1;
			}
		}

		if (count > max_count) {
			max_count = count;
			max = cur;
		}

		cout << max << endl;
	}
}
