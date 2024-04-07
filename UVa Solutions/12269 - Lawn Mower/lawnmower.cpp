#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int X, Y;
double W;

bool isFull(vector<double> &v, double w, int total) {
	double last = w / 2;

	for (int i = 0; i < v.size(); i++) {
		if (v[i] > last) {
			return false;
		}

		last = v[i] + w;
	}

	if (last - w / 2 < total) return false;
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> X >> Y >> W) {
		if (X == 0 && Y == 0 && W == 0.0) break;

		vector<double> XP(X);
		vector<double> YP(Y);

		for (int i = 0; i < X; i++) {
			cin >> XP[i];
		}

		for (int i = 0; i < Y; i++) {
			cin >> YP[i];
		}

		sort(XP.begin(), XP.end());
		sort(YP.begin(), YP.end());

		if (isFull(XP, W, 75) && isFull(YP, W, 100)) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
