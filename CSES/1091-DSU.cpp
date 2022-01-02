#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct DSU {
	vector<int> f;
	DSU (int n) : f(n) {
		for (int i = 0; i < n; ++i)
			f[i] = i;
	}
	int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	void M(int u, int v) {
		u = F(u); v = F(v);
		f[v] = u;
	}
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cout.tie(0) -> sync_with_stdio(0);

	int n, m; cin >> n >> m;
	vector<int> h(n);
	for (int &i: h) cin >> i;
	h.emplace_back(-1);
	sort(begin(h), end(h));

	DSU dsu(n + 1);
	for (int t, i = 0; i < m; ++i) {
		cin >> t;
		int p = upper_bound(begin(h), end(h), t) - begin(h) - 1;
		p = dsu.F(p);
		cout << h[p] << '\n';
		if (p != 0) dsu.M(p - 1, p);
	}

	return 0;
}
