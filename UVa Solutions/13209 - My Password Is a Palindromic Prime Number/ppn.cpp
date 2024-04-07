#include <iostream>
#include <vector>
using namespace std;

typedef int lli;

void divide_p(lli a, lli b) {
	vector<bool> visited(10e5, false);
	visited[a] = true;

	if (a == b) {
		cout << 1;
		return;
	}

	cout << "0.";
	a *= 10;

	while (!visited[a]) {
		visited[a] = true;

		if (a < b) {
			cout << 0;
			a *= 10;
		} else {
			cout << a / b;
			a = (a % b) * 10;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	lli p;
	cin >> t;

	for (int i = 0; i < t; ++i) {
		cin >> p;
		divide_p(1, p);
		cout << "\n";
	}

	return 0;
}
