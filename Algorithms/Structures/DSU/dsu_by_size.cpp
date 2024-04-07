#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> parents;
vector<int> sizes;

void make_set(int val) {
	parents[val] = val;
	sizes[val] = 1;
}

int find_set(int val) {
	if (parents[val] == val) return val;
	return parents[val] = find_set(parents[val]);
}

void union_set(int val1, int val2) {
	int root1 = find_set(val1);
	int root2 = find_set(val2);

	if (root1 != root2) {
		if (sizes[root1] < sizes[root2]) {
			swap(root1, root2);
		}

		parents[root1] = root2;
		sizes[root1] += sizes[root2];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	parents.resize(N + 1);
	sizes.resize(N + 1);

	for (int i = 1; i <= N; i++) {
		make_set(i);
	}

	int val1, val2;
	char c;

	while (cin >> c) {
		if (c == 'u') {
			cin >> val1 >> val2;
			union_set(val1, val2);
		} else if (c == 'f') {
			cin >> val1;
			cout << find_set(val1) << '\n';
		}
	}

	return 0;
}
