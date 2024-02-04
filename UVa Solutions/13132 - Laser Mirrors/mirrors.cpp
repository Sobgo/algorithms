#include <iostream>
#include <vector>
using namespace std;

vector <int> phi;

void precomp_phi(int range) {
	phi.resize(range + 1);

	for (int i = 0; i <= range; ++i) phi[i] = i;

	for (int i = 2; i <= range; ++i) {
		if (phi[i] == i) {
			for (int j = i; j <= range; j += i) {
				phi[j] -= phi[j] / i;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	precomp_phi((int)1e5);

	int n, x;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> x;
		cout << phi[x] << '\n';
	}

	return 0;
}
