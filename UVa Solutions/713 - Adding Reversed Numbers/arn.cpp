#include <iostream>
using namespace std;

void print(string s) {
	int iter = 0;

	while (iter < s.size() && s[iter] == '0') ++iter;

	if (iter == s.size()) cout << 0;
	else {
		for (int i = iter; i < s.size(); ++i) cout << s[i];
	}
}

string add(string &a, string &b) {
	string res;
	int carry = 0, sum;

	int s = a.size() > b.size() ? b.size() : a.size();

	for (int i = 0; i < s; ++i) {
		sum = carry;
		sum += a[i] - '0';
		sum += b[i] - '0';

		res.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	for (int i = s; i < a.size(); ++i) {
		sum = carry;
		sum += a[i] - '0';

		res.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	for (int i = s; i < b.size(); ++i) {
		int sum = carry;
		sum += b[i] - '0';

		res.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	if (carry) res.push_back(carry + '0');

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string a, b;
	int t;

	cin >> t;

	for (int i = 0; i < t; ++i) {
		cin >> a >> b;
		print(add(a, b));
		cout << "\n";
	}

	return 0;
}
