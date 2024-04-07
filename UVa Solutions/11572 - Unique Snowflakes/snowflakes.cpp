#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t-- > 0) {
		int n;
		cin >> n;
		vector<int> snowflakes(n);
		map<int, int> present;

		for (int i = 0; i < n; ++i) {
			cin >> snowflakes[i];
		}

		int max_len = 0, len = 0;
		int start = 0, end = 0;

		while (end < n) {
			if (present[snowflakes[end]] != 0) {
				max_len = max(max_len, len);

				while (present[snowflakes[end]] != 0) {
					present[snowflakes[start]]--;
					start++;
					len--;
				}
			}

			present[snowflakes[end]]++;
			len++;
			end++;
		}

		max_len = max(max_len, len);

		cout << max_len << "\n";
	}

	return 0;
}
