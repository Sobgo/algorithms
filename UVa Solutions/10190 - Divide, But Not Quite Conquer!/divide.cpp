#include <iostream>
#include <queue>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long int n, m, div;

	while (cin >> n >> m) {
		queue<long long int> q;

		if (n == 0 || m == 0 || m == 1 || n < m) {
			cout << "Boring!\n";
			continue;
		}

		div = n;

		while (div % m == 0) {
			q.push(div);
			div /= m;
		}

		if (div == 1) {
			q.push(1);

			while (q.size() > 1) {
				cout << q.front() << " ";
				q.pop();
			}
			cout << q.front() << "\n";
		} else {
			cout << "Boring!\n";
		}
	}

	return 0;
}
