#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct Node {
	array<Node *, 26> children;
	int letters;
	bool isWord;

	Node() {
		isWord = 0;
		letters = 0;

		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}

	~Node() {
		for (int i = 0; i < 26; i++) {
			if (children[i] != nullptr) {
				delete children[i];
			}
		}
	}
};

class Trie {
	Node *root;

	int dfs(Node *node, int branch = 0) {
		int total = 0;

		for (int i = 0; i < 26; i++) {
			if (node->children[i] != nullptr) {
				if (node->isWord || node->letters > 1) {
					total += dfs(node->children[i], branch + 1);
				} else {
					total += dfs(node->children[i], branch);
				}
			}
		}

		if (node->isWord) {
			total += branch;
		}

		return total;
	}

  public:
	Trie() {
		root = new Node();
		root->isWord = true;
	}

	void addWord(string word) {
		Node *current = root;

		for (char &c : word) {
			int index = c - 'a';

			if (current->children[index] == nullptr) {
				current->children[index] = new Node();
				current->letters++;
			}

			current = current->children[index];
		}

		current->isWord = true;
	}

	int dfs() { return dfs(root); }
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;

	while (cin >> n) {
		Trie trie;
		string word;

		for (int i = 0; i < n; i++) {
			cin >> word;
			trie.addWord(word);
		}

		cout << fixed << setprecision(2)
			 << (floor(((double)trie.dfs() / n * 100) + 0.5)) / 100 << "\n";
	}

	return 0;
}
