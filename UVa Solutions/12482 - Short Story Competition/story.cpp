#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, l, c;

	while (cin >> n >> l >> c) {
		vector<string> v(n);
		string s;

		for (int i = n - 1; i >= 0; --i) {
			cin >> s;
			v[i] = s;
		}

		int p = 0, li = 0, ch = 0;

		while (v.size() != 0) {
			while (v.size() != 0 && ch + v.back().size() <= c) {
				ch += v.back().size() + 1;
				v.pop_back();
			}

			li += 1;
			ch = 0;

			if (li > l) {
				li = 1;
				p += 1;
			}
		}

		if (li != 0) {
			p += 1;
		}

		cout << p << "\n";
	}

	return 0;
}
