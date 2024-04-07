#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef string::iterator s_it;

int n;
string pre, in;

void post(int root, s_it is, s_it ie) {
	if (is > ie) return;

	s_it ir = find(is, ie, pre[root]);

	post(root + 1, is, ir - 1);
	post(root + 1 + distance(is, ir), ir + 1, ie);

	cout << pre[root];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t-- > 0) {
		cin >> n >> pre >> in;
		post(0, in.begin(), in.end() - 1);
		cout << '\n';
	}

	return 0;
}
