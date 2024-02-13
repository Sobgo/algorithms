#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

#define x first
#define y second

#define make_t2i make_pair
#define make_t3i make_pair

typedef pair <int, int> t2i;
typedef pair < pair <int, int>, int> t3i;
typedef vector <t2i> vt2i;

const int B_SIZE = 8;

vector < vector <vt2i> > adj(B_SIZE, vector <vt2i>(B_SIZE));

int abs(int x) { return x < 0 ? -x : x; }

bool in_range(t2i &p) {
	return p.x >= 0 && p.x < B_SIZE && p.y >= 0 && p.y < B_SIZE;
}

bool possible(t2i s, t2i e) {
	if (!in_range(s) || !in_range(e)) return false;

	int xx = abs(s.x - e.x);
	int yy = abs(s.y - e.y);
	return (xx == 1 && yy == 2) || (xx == 2 && yy == 1);
}

void populate_adj() {
	int X[B_SIZE] = {1, 2, -1, -2, 1, 2, -1, -2};
	int Y[B_SIZE] = {2, 1, 2, 1, -2, -1, -2, -1};

	for (int i = 0; i < B_SIZE; ++i) {
		for (int j = 0; j < B_SIZE; j++) {
			for (int pos = 0; pos < B_SIZE; ++pos) {
				if (possible(make_t2i(i, j), make_t2i(i + X[pos], j + Y[pos]))) {
					adj[i][j].push_back(make_t2i(i + X[pos], j + Y[pos]));
				}
			}
		}
	}
}

int bfs(t2i s, t2i e) {
	queue <t3i> q;
	t2i node;
	int depth;

	vector < vector <bool> > visited(B_SIZE, vector <bool>(B_SIZE, false));

	q.push(make_t3i(s, 0));
	visited[s.x][s.y] = true;

	while (!q.empty()) {
		node = q.front().first;
		depth = q.front().second;
		q.pop();

		if (node.x == e.x && node.y == e.y) return depth;

		for (int i = 0; i < adj[node.x][node.y].size(); ++i) {
			t2i next = adj[node.x][node.y][i];

			if (!visited[next.x][next.y]) {
				visited[next.x][next.y] = true;
				q.push(make_t3i(next, depth + 1));
			}
		}
	}

	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	populate_adj();

	string str;
	t2i s, e;

	while (cin >> str) {
		s = make_t2i(str[0] - 'a', str[1] - '1');
		cin >> str;
		e = make_t2i(str[0] - 'a', str[1] - '1');

		cout << "To get from " << char(s.x + 'a') << s.y + 1;
		cout << " to " << char(e.x + 'a') << e.y + 1;
		cout << " takes " << bfs(s, e) << " knight moves.\n";
	}

	return 0;
}
