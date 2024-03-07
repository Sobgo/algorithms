#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N;
vector < vector <int> > capacity;
vector < vector <int> > adj;

int bfs(int s, int t, vector <int> &parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue < pair <int, int> > q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector <int> parent(N);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;

        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

    map <string, int> mp;
    string s1, s2;

    int t; cin >> t;
    int n, m;

	for (int tc = 0; tc < t; ++tc) {
        cin >> n >> m;

        N = m + 6 + 2;
        int w = n/6;

        capacity.assign(N, vector<int>(N, 0));
        adj.assign(N, vector<int>());
        mp.clear();

        int s = adj.size() - 2, e = adj.size() - 1;
        vector <string> sizes = {"XS", "S", "M", "L", "XL", "XXL"};

        for (int i = 0; i < 6; ++i) {
            mp[sizes[i]] = m + i;
            adj[m+i].push_back(e);
            adj[e].push_back(m+i);
            capacity[m+i][e] = w;
        }

        for (int i = 0; i < m; ++i) {
            adj[s].push_back(i);
            adj[i].push_back(s);
            capacity[s][i] = 1;

            cin >> s1 >> s2;
            adj[i].push_back(mp[s1]);
            adj[mp[s1]].push_back(i);
            capacity[i][mp[s1]] = 1;

            adj[i].push_back(mp[s2]);
            adj[mp[s2]].push_back(i);
            capacity[i][mp[s2]] = 1;
        }

        if (maxflow(s, e) >= m) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

	return 0;
}
