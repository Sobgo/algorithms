#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <map>
using namespace std;

typedef vector <bool> vb;
typedef vector <int> vi;
typedef vector <vi> vvi;

void dfs(int node, int &idx, vvi &adj, vi &ids, vi &low, stack <int> &s, vb &on_stack) {
	ids[node] = low[node] = idx++;
	s.push(node);
	on_stack[node] = true;

	for (int i = 0; i < adj[node].size(); ++i) {
		int next = adj[node][i];

		if (ids[next] == -1) dfs(next, idx, adj, ids, low, s, on_stack);
		if (on_stack[next]) low[node] = min(low[node], low[next]);
	}

	if (ids[node] == low[node]) {
		while (!s.empty()) {
			low[s.top()] = low[node];
			on_stack[s.top()] = false;
			if (s.top() == node) break;
			s.pop();
		}

		s.pop();
	}
}

vector <vector <int> > find_scc(vvi &adj) {
	stack <int> s;
	vb on_stack(adj.size());
	vi ids(adj.size(), -1), low(adj.size(), -1);
	int idx = 0;

	for (int i = 0; i < adj.size(); ++i) {
		if (ids[i] != -1) continue;
		dfs(i, idx, adj, ids, low, s, on_stack);
	}

	vector < vector <int> > components(adj.size());

	for (int i = 0; i < adj.size(); ++i) {
		components[low[i]].push_back(i);
	}

	return components;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, t = 1;
	while(cin >> n >> m) {
		if (n == 0 && m == 0) break;

		if (m == 0) {
			cout << "Calling circles for data set " << t++ << ":\n\n";
			continue;
		}

		map <string, int> M;
		vector <string> RM;

		string s1, s2;
		vector < vector <int> > adj(n);

		for (int i = 0; i < m; ++i) {
			cin >> s1 >> s2;

			if (M.find(s1) == M.end()) {
				M[s1] = M.size();
				RM.push_back(s1);
			}

			if (M.find(s2) == M.end()) {
				M[s2] = M.size();
				RM.push_back(s2);
			}

			adj[M[s1]].push_back(M[s2]);
		}

		vector < vector <int> > components = find_scc(adj);

		cout << "Calling circles for data set " << t++ << ":\n";

		for (int i = 0; i < components.size(); ++i) {
			for (int j = 0; j < components[i].size(); ++j) {
				cout << RM[components[i][j]];
				if (j != components[i].size()-1) cout << ", ";
			}
			if (components[i].size() != 0) cout << '\n';
		}

		cout << '\n';
	}

	return 0;
}
