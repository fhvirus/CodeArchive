#include<bits/stdc++.h>
using namespace std;

const int kN = 200002;
mt19937 mt((unsigned)chrono::system_clock::now().time_since_epoch().count());

struct Node {
	int64_t val, sum;
	unsigned pri, siz;
	bool tag;
	int lc, rc;
	Node() = default;
	Node(int64_t v): val(v), sum(v), pri(mt()), siz(1), tag(false), lc(0), rc(0) {}
} nds[kN];

int newNode(int64_t val) {
	static int tot = 0;
	nds[++tot] = Node(val);
	return tot;
}
void upd(int u) {
	swap(nds[u].lc, nds[u].rc);
	nds[u].tag ^= 1;
}
void pull(int u) {
	nds[u].siz = nds[nds[u].lc].siz + 1 + nds[nds[u].rc].siz;
	nds[u].sum = nds[nds[u].lc].sum + nds[u].val + nds[nds[u].rc].sum;
}
void push(int u) {
	if (nds[u].tag) {
		upd(nds[u].lc);
		upd(nds[u].rc);
		nds[u].tag = false;
	}
}

int merge(int u, int v) {
	if (u == 0 or v == 0)
		return u == 0 ? v : u;
	if (nds[u].pri > nds[v].pri) {
		push(u);
		nds[u].rc = merge(nds[u].rc, v);
		pull(u);
		return u;
	} else {
		push(v);
		nds[v].lc = merge(u, nds[v].lc);
		pull(v);
		return v;
	}
}
void split_by_size(int o, int& u, int& v, int k) {
	if (o == 0) {
		u = v = 0;
		return;
	}
	push(o);
	int lsz = nds[nds[o].lc].siz + 1;
	if (lsz <= k) {
		u = o;
		split_by_size(nds[o].rc, nds[u].rc, v, k - lsz);
		pull(u);
	} else {
		v = o;
		split_by_size(nds[o].lc, u, nds[v].lc, k);
		pull(v);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	int root = 0;
	for (int x, i = 1; i <= n; ++i) {
		cin >> x;
		root = merge(root, newNode(x));
	}

	for (int t, a, b, i = 0; i < m; ++i) {
		cin >> t >> a >> b;
		int tmp, left, mid, right;
		split_by_size(root, tmp, right, b);
		split_by_size(tmp, left, mid, a - 1);

		if (t == 1) {
			upd(mid);
		} else {
			cout << nds[mid].sum << '\n';
		}

		root = merge(left, merge(mid, right));
	}

	return 0;
}
