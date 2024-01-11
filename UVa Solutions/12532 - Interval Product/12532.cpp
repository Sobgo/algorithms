#include <iostream>
#include <vector>
using namespace std;

int clamp(int val, int min_val, int max_val) {
	if (val < min_val) return min_val;
	if (val > max_val) return max_val;
	return val;
}

class SegmentTree {
  protected:
	int m_size;
	vector <int> m_tree;

	void build(vector <int> &input, int idx, int l, int r) {
		if (l == r) {
			m_tree[idx] = input[l];
			return;
		}

		int mid = (l + r) / 2;
		build(input, 2*idx, l, mid);
		build(input, 2*idx + 1, mid + 1, r);
		m_tree[idx] = m_tree[2*idx] * m_tree[2*idx + 1];
	}

	int query(int ql, int qr, int idx, int l, int r) {
		if (ql > qr) return 1;
		if (l == ql && r == qr) return m_tree[idx];

		int mid = (l + r) / 2;
		
		return
			query(ql, min(mid, qr), idx*2, l, mid) * 
			query(max(ql, mid + 1), qr, idx*2 + 1, mid + 1, r); 
	}

	void update(int pos, int val, int idx, int l, int r) {
		if (l == r) {
			m_tree[idx] = val;
			return;
		}

		int mid = (l + r) / 2;

		if (pos <= mid) update(pos, val, 2*idx, l, mid);
		else update(pos, val, 2*idx + 1, mid + 1, r);

		m_tree[idx] = m_tree[2*idx] * m_tree[2*idx + 1];
	}

  public:
	SegmentTree(vector <int> &input) {
		build(input);
	}

	void build(vector <int> &input) {
		m_size = input.size();
		m_tree = vector <int> (4*m_size);
		build(input, 1, 0, m_size - 1);
	}

	int query(int ql, int qr) {
		return query(ql, qr, 1, 0, m_size - 1);
	}

	void update(int pos, int val) {
		update(pos, val, 1, 0, m_size - 1);
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	char c;

	while(cin >> n >> m) {
		vector <int> input(n);
		for (int i = 0; i < n; ++i) {
			cin >> input[i];
			input[i] = clamp(input[i], -1, 1);
		}

		SegmentTree st(input);

		for (int i = 0; i < m; ++i) {
			cin >> c;

			if (c =='C') {
				int pos, val;
				cin >> pos >> val;

				pos--;
				val = clamp(val, -1, 1);

				st.update(pos, val);
				
			} else if (c == 'P') {
				int ql, qr;
				cin >> ql >> qr;

				ql--; qr--;

				int res = st.query(ql, qr);

				if (res == 0) cout << "0";
				else if (res < 0) cout << "-";
				else cout << "+";	
			}
		}

		cout << "\n";
	}

	return 0;
}
