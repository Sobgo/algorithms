#include <iostream>
#include <vector>
using namespace std;

using lli = long long int;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;

	while (cin >> n) {
		vector<lli> length(3, 0);
		vector<lli> height(3, 0);
		lli x;

		for (int i = 0; i < n; ++i) {
			cin >> x;
			length[i % 3] += x;
		}

		for (int i = 0; i < n; ++i) {
			cin >> x;
			height[i % 3] += x;
		}

		cout << length[2] * height[2] + length[0] * height[1] + length[1] * height[0] << " ";
		cout << length[1] * height[1] + length[2] * height[0] + length[0] * height[2] << " ";
		cout << length[0] * height[0] + length[1] * height[2] + length[2] * height[1] << "\n";
	}

	return 0;
}
