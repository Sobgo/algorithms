#include <iostream>
#include <vector>
using namespace std;

vector <int> l, r;
vector < vector <int> > cache;

int solve(int i, int j) {
    if (i == l.size() || j == r.size()) return 0;
    if (cache[i][j] != -1) return cache[i][j];

    int result = 0;

    if (l[i] == r[j]) {
        result = 1 + solve(i + 1, j + 1);
    } else {
        result = max(solve(i + 1, j), solve(i, j + 1));
    }

    return cache[i][j] = result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    int iter = 0;

    while(true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        l.resize(n);
        r.resize(m);
        cache.resize(n, vector <int>(m, -1));

        for (int i = 0; i < n; i++) {
            cin >> l[i];
        }

        for (int i = 0; i < m; i++) {
            cin >> r[i];
        }

        cout << "Twin Towers #" << ++iter << "\n";
        cout << "Number of Tiles : " << solve(0, 0) << "\n\n";

        l.clear();
        r.clear();
        cache.clear();
    }

    return 0;
}
