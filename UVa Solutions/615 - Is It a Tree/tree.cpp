#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <cstdlib>
using namespace std;

typedef vector <bool> vb;
typedef vector < vector <int> > vvi;

pair <bool, int> DFS(int node, vvi &adj, vb &visited) {
	if (visited[node]) return make_pair(false, 0);
	visited[node] = true;

	int total = 1;

	for (int i = 0; i < adj[node].size(); ++i) {
		pair <bool, int> res = DFS(adj[node][i], adj, visited);
		if (!res.first) return make_pair(false, 0);
		total += res.second;
	}

	return make_pair(true, total);
}

pair <vvi, vvi> read_adj() {
	map <int, int> mp;
	queue < pair <int, int> > q;
	int a, b, iter = 0;

	while (true) {
		cin >> a >> b;

		if (a == 0 && b == 0) break;
		if (a < 0 || b < 0) exit(0);

		if (mp.find(a) == mp.end()) {
			mp.insert(make_pair(a, iter));
			iter++;
		}

		if (mp.find(b) == mp.end()) {
			mp.insert(make_pair(b, iter));
			iter++;
		}

		q.push(make_pair(mp[a], mp[b]));
	}

	vvi adj(iter);
	vvi rev(iter);

	while (!q.empty()) {
		a = q.front().first;
		b = q.front().second;
		q.pop();

		adj[a].push_back(b);
		rev[b].push_back(a);
	}

	return make_pair(adj, rev);
}

int find_root(vvi &adj) {
	int root = -1;

	for (int i = 0; i < adj.size(); ++i) {
		if (adj[i].size() == 0) {
			if (root != -1) return -1;
			root = i;
		}

		if (adj[i].size() > 1) return -1;
	}

	return root;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, iter = 1;

	while (true) {
		pair<vvi, vvi> res = read_adj();

		if (res.first.size() == 0) {
			cout << "Case " << iter << " is a tree.\n";
			iter++;
			continue;
		}

		int root = find_root(res.second);

		if (root == -1) {
			cout << "Case " << iter << " is not a tree.\n";
			iter++;
			continue;
		}

		vb visited(res.first.size());
		pair <bool, int> res2 = DFS(root, res.first, visited);

		if (res2.first && (res2.second == res.first.size())) {
			cout << "Case " << iter << " is a tree.\n";
		} else {
			cout << "Case " << iter << " is not a tree.\n";
		}

		iter++;
	}

	return 0;
}

