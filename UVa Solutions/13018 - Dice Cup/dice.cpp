#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while (cin >> N >> M) {
		vector <int> rolls(N + M + 1, 0);

		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				rolls[i+j]++;
			}
		}

		int max_val = -1;
		queue <int> idx;

		for (int i = 0; i < rolls.size(); ++i) {
			if (rolls[i] > max_val) {
				idx = queue <int>(); // clear
				idx.push(i);
				max_val = rolls[i];
			} else if (rolls[i] == max_val) {
				idx.push(i);
			}
		}

		while (!idx.empty()) {
			cout << idx.front() << "\n";
			idx.pop();
		}

		cout << "\n";
	}

	return 0;
}
