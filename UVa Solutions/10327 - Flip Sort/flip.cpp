#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int lli;

lli counter = 0;
lli total = 0;

template <typename RandomIt>
void mergesort(RandomIt first, RandomIt last) {
	if (last - first > 1) {
		RandomIt middle = first + (last - first) / 2;

		mergesort(first, middle);
		mergesort(middle, last);

		counter = middle - first;

		using value_type = typename iterator_traits<RandomIt>::value_type;

		inplace_merge(first, middle, last, [](const value_type &a, const value_type &b) mutable {
			if (a < b) {
				total += counter;
				return true;
			}
			counter--;
			return false;
		});
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;

	while (cin >> n) {
		vector<lli> v;
		lli x;

		for (int i = 0; i < n; ++i) {
			cin >> x;
			v.push_back(x);
		}

		mergesort(v.begin(), v.end());
		cout << "Minimum exchange operations : " << total << "\n";
		total = 0;
	}

	return 0;
}
