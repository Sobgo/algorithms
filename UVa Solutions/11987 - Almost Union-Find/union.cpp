#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100000

int n, m;
vector <int> parents (MAXN*2 + 1);
vector <int> sizes (MAXN*2 + 1);
vector <int> sums (MAXN*2 + 1);

void make_set(int val) {
	int m = val + n;

	parents[val] = m;
	parents[m] = m;
	sizes[m] = 1;
	sums[m] = val;
}

int find_set(int val) {
	if (parents[val] == val) return val;
	return parents[val] = find_set(parents[val]);
}

void union_sets(int a, int b) {
    int a_root = find_set(a);
    int b_root = find_set(b);

    if (a_root != b_root) {
		if (sizes[a_root] < sizes[b_root]) swap(a_root, b_root);
		parents[b_root] = a_root;
		sizes[a_root] += sizes[b_root];
		sums[a_root] += sums[b_root];
    }
}

void move_elem(int a, int b) {
	int a_root = find_set(a);
	int b_root = find_set(b);

	if (a_root != b_root) {
		parents[a] = b_root;
		sizes[a_root]--;
		sizes[b_root]++;
		sums[a_root] -= a;
		sums[b_root] += a;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> n >> m) {
		for (int i = 1; i <= n; ++i) {
			make_set(i);
		}

		int d, p, q;

		for (int i = 0; i < m; ++i) {
			cin >> d;

			if (d == 1) {
				cin >> p >> q;
				union_sets(p, q);
			} else if (d == 2) {
				cin >> p >> q;
				move_elem(p, q);
			} else if (d == 3) {
				cin >> p;
				int root = find_set(p);
				cout << sizes[root] << " " << sums[root] << "\n";
			}
		}
	}

	return 0;
}
