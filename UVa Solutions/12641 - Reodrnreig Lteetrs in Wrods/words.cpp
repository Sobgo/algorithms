#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	cin.ignore();

	while (t-- > 0) {
		string in;
		getline(cin, in);

		stringstream ss(in);
		unordered_map<string, string> word_map;

		for (string word; ss >> word;) {
			string start = string(word.front(), word.back());
			string rest = word.substr(1, word.size() - 2);
			sort(rest.begin(), rest.end());

			if (word_map.find(start + rest) == word_map.end()) {
				word_map.insert({start + rest, word});
			} else {
				if (word_map[start + rest] > word) {
					word_map[start + rest] = word;
				}
			}
		}

		getline(cin, in);
		ss = stringstream(in);

		for (string word; ss >> word;) {
			string start = string(word.front(), word.back());
			string rest = word.substr(1, word.size() - 2);
			sort(rest.begin(), rest.end());

			if (word_map.find(start + rest) != word_map.end()) {
				cout << word_map[start + rest] << " ";
			} else {
				cout << word << " ";
			}
		}

		cout << "\n";
	}

	return 0;
}
