#include <iostream>
using namespace std;

int N;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s;
	int m;

	while (cin >> N) {
		if (N == 0) break;

		int stack1 = 0, stack2 = 0;

		for (int i = 0; i < N; ++i) {
			cin >> s >> m;

			if (s  == "DROP") {
				cout << "DROP 2 " << m << "\n";
				stack1 += m;
			} else if (s == "TAKE") {
				while (m > 0) {
					if (stack2 != 0) {
						int mini = min(m, stack2);

						cout << "TAKE 1 " << mini << "\n";
						m -= mini;
						stack2 -= mini;
					} else {
						cout << "MOVE 2->1 " << stack1 << "\n";
						stack2 = stack1;
						stack1 = 0;
					}
				}
			}
		}
		cout << "\n";
	}

	return 0;
}
