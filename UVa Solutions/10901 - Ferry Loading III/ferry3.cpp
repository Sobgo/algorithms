#include <queue>
#include <iostream>
#include <vector>
using namespace std;

void ferry() {
	int n, t, m;
	cin >> n >> t >> m;

	vector < queue <int> > sides(2);
	vector <int> out_time(m);

	for (int i = 0; i < m; ++i) {
		int arrival; string side;
		cin >> arrival >> side;

		if (side == "left") sides[0].push(i);
		else sides[1].push(i);

		out_time[i] = arrival;
	}

	int time = 0, cap = 0, side = 0;

	while (!sides[0].empty()|| !sides[1].empty()) {

		if (sides[0].empty()) {
			time = max(time, out_time[sides[1].front()]);
		} else if (sides[1].empty()) {
			time = max(time, out_time[sides[0].front()]);
		} else {
			time = max(time, min(out_time[sides[0].front()], out_time[sides[1].front()]));
		}

		while (!sides[side].empty() && out_time[sides[side].front()] <= time && cap < n) {
			out_time[sides[side].front()] = time + t;
			sides[side].pop();
			cap++;
		}

		time += t;
		cap = 0;
		side = (side + 1) % 2;
	}

	for (int i = 0; i < out_time.size(); ++i) {
		cout << out_time[i] << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c; cin >> c;

	for (int i = 1; i < c; ++i) {
		ferry(); cout << "\n";
	}
	
	if (c > 0) ferry();

	return 0;
}
