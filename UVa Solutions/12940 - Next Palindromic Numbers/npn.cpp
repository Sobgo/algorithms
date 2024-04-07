#include <iostream>
#include <string>
using namespace std;

bool increment(string::iterator s, string::iterator e) {
	for (auto it = e - 1; it >= s; it--) {
		(*it)++;
		if (*it <= '9') return false;
		*it = '0';
	}

	return (*s == '0');
}

string next_palindrome(string &num) {
	string res;

	bool ap = increment(num.begin(), num.end());
	if (ap) num.insert(num.begin(), '1');

	res.append(num.begin(), num.begin() + (num.size() + 1) / 2);
	res.append(num.rbegin() + (num.size() + 1) / 2, num.rend());

	if (res < num) {
		ap = increment(res.begin(), res.begin() + (res.size() - 1) / 2 + 1);
		if (ap) num.insert(num.begin(), '1');

		int mid = (res.size() - 1) / 2;
		for (int j = 0; j <= mid; ++j) {
			res[res.size() - j - 1] = res[j];
		}
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	string s;

	while (cin >> n >> s) {
		for (int i = 0; i < n; ++i) {
			s = next_palindrome(s);
			cout << s << "\n";
		}
	}

	return 0;
}
