#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define INF (int)1e9

int H, W, G, E;
vector < vector <int> > grid;
vector < tuple <int, int, int> > holes;
vector < vector <int> > dist;

void bellman_ford(int sx, int sy) {
	int dest_x, dest_y, t;
	vector <int> dx = { 0, 0, 1, -1 };
	vector <int> dy = { 1, -1, 0, 0 };

	dist[sx][sy] = 0;

	for (int ii = 1; ii <= H; ++ii) {
		for (int jj = 1; jj <= W; ++jj) {
			for (int i = 1; i <= H; ++i) {
				for (int j = 1; j <= W; ++j) {	
					if (dist[i][j] == INF) continue;
					if (i == H && j == W) continue;

					if (grid[i][j] > 0) {
						tie(dest_x, dest_y, t) = holes[grid[i][j]];	
						if (dist[i][j] + t < dist[dest_x][dest_y]) {
							dist[dest_x][dest_y] = dist[i][j] + t;
						}
					} else {
						for (int k = 0; k < 4; ++k) {
							dest_x = i + dx[k];
							dest_y = j + dy[k];

							if (grid[dest_x][dest_y] == -1) continue;

							if (dist[i][j] + 1 < dist[dest_x][dest_y]) {
								dist[dest_x][dest_y] = dist[i][j] + 1;
							}
						}
					}
				}
			}
		}
	}

	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {	
			if (dist[i][j] == INF) continue;
			if (i == H && j == W) continue;
			
			if (grid[i][j] > 0) {
				tie(dest_x, dest_y, t) = holes[grid[i][j]];	
				if (dist[i][j] + t < dist[dest_x][dest_y]) {
					dist[H][W] = -INF;
					return;
				}
			} else {
				for (int k = 0; k < 4; ++k) {
					dest_x = i + dx[k];
					dest_y = j + dy[k];

					if (grid[dest_x][dest_y] == -1) continue;

					if (dist[i][j] + 1 < dist[dest_x][dest_y]) {
						dist[H][W] = -INF;
						return;
					}
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> H >> W) {
		if (H == 0 && W == 0) break;

		grid = vector < vector <int> >(H+2, vector <int>(W+2, 0));

		for (int i = 0; i <= H+1; ++i) {
			grid[i][0] = -1;
			grid[i][W+1] = -1;
		}

		for (int i = 0; i <= W+1; ++i) {
			grid[0][i] = -1;
			grid[H+1][i] = -1;
		}

		cin >> G;

		int x, y;
		for (int i = 0; i < G; ++i) {
			cin >> x >> y;
			grid[x+1][y+1] = -1;
		}

		cin >> E;

		holes = vector < tuple <int, int, int> >(E+1);

		int to_x, to_y, t;
		for (int i = 1; i <= E; ++i) {
			cin >> x >> y >> to_x >> to_y >> t;
			holes[i] = { to_x+1, to_y+1, t };
			grid[x+1][y+1] = i;
		}

		dist = vector < vector <int> >(H+2, vector <int>(W+2, INF));

		bellman_ford(1, 1);

		if (dist[H][W] == INF) {
			cout << "Impossible\n";
		} else if (dist[H][W] == -INF) {
			cout << "Never\n";
		} else {
			cout << dist[H][W] << '\n';
		}
	}

	return 0;
}
