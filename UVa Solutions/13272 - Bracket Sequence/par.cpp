#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool is_closing(char &c) {
	return c == '}' || c == ']' || c == ')' || c == '>';
}

char opening(char &c) {
	if (c == ')') return '(';
	return c - 2;
}

vector<int> par(string &s) {
	stack<int> st;
	int total = 0;

	vector<int> max_balanced(s.size(), 0);

	for (int i = 0; i < s.size(); ++i) {
		if (is_closing(s[i])) {
			if (!st.empty() && s[st.top()] == opening(s[i])) {
				max_balanced[st.top()] = max(max_balanced[st.top()], i - st.top() + 1);
				st.pop();
			} else {
				st = stack<int>(); // clear
			}
		} else {
			st.push(i);
		}
	}

	for (int i = max_balanced.size() - 3; i >= 0; --i) {
		max_balanced[i] = max_balanced[i] + max_balanced[i + max_balanced[i]];
	}

	return max_balanced;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	string s;

	for (int tc = 1; tc <= t; ++tc) {
		cin >> s;

		cout << "Case " << tc << ":\n";
		for (int &val : par(s)) cout << val << "\n";
	}

	return 0;
}
