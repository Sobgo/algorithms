#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
using namespace std;

typedef vector <bool> vb;
typedef vector <int> vi;
typedef vector < vector <int> > vvi;

void dfs(int node, vvi &adj, vb &visited, vi &topo_order, int &iter) {
	if (visited[node]) return;
	visited[node] = true;

	for (int i = 0; i < adj[node].size(); ++i) {
		dfs(adj[node][i], adj, visited, topo_order, iter);
	}

	topo_order[iter--] = node;
}

pair <int, int> order(string &a, string &b) {
	int n = a.size();
	int m = b.size();

	int i = 0;
	while (i < n && i < m && a[i] == b[i]) ++i;

	if (i == n || i == m) return make_pair(-1, -1);
	return make_pair(a[i] - 'A' , b[i] - 'A');
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s;
	int N = 0;
	vector <int> M(26, -1);
	vector <char> RM;
	vector <string> words;

	while (cin >> s) {
		if (s != "#") {
			words.push_back(s);

			for (int i = 0; i < s.size(); ++i) {
				if (M[s[i]-'A'] == -1) {
					M[s[i]-'A'] = N++;
					RM.push_back(s[i]);
				}
			}
		} else {
			vector < vector <int> > adj(N);
			set < pair <int, int> > edges;

			for (int i = 0; i < words.size()-1; ++i) {
				pair <int, int> edge = order(words[i], words[i+1]);
				if (edge.first != -1) edges.insert(edge);
			}

			set < pair <int, int> >::iterator it;
			for (it = edges.begin(); it != edges.end(); ++it) {
				adj[M[it->first]].push_back(M[it->second]);
			}

			vector <int> topo_order(N);
			vector <bool> visited(N);
			int iter = N - 1;

			for (int i = 0; i < N; ++i) {
				if (!visited[i]) {
					dfs(i, adj, visited, topo_order, iter);
				}
			}

			for (int i = 0; i < N; ++i) {
				cout << RM[topo_order[i]];
			}

			cout << '\n';

			N = 0;
			M.assign(26, -1);
			RM.clear();
			words.clear();
		}
	}

	return 0;
}
