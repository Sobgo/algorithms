#include <iostream>
#include <vector>
using namespace std;

#define s first
#define e second

int N, M;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> N >> M) {
		if (N == 0 && M == 0) break;

		vector < pair <int, int> > con(N);
		vector < pair <int, int> > inter(M);

		int a, b;
		for (int i = 0; i < N; ++i) {
			cin >> a >> b >> con[i].s >> con[i].e;
			con[i].second = con[i].s + con[i].e;
		}

		for (int i = 0; i < M; ++i) {
			cin >> inter[i].s >> inter[i].e;
			inter[i].e= inter[i].s + inter[i].e;
		}

		for (int i = 0; i < M; ++i) {
			int count = 0;

			for (int j = 0; j < N; ++j) {
				if (inter[i].s >= con[j].e || inter[i].e <= con[j].s) continue;
				count++;
			}

			cout << count << "\n";
		}
	}

	return 0;
}
