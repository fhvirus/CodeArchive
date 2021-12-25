#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// Brief Editorial:
// Let's select a spanning forest "S" for the graph.
// The set of edges E - S can be selected randomly.
// Consider a leaf "u" in S. Whether or not we choose
// the edge connecting u is determined by the way we
// choose other edges in E - S. And by some kind of
// induction, it can be proven that all the edges in
// S is determined by the edges in E - S. Thus, the
// answer is 2 ^ |E - S|.
// But what is |S| ? By some observation we can see
// that |S| is equal to n - (# of connected components)

struct DSU {
	vector<int> f; int cc;
	DSU (int n): cc(n), f(n+1, 0) { iota(begin(f), end(f), 0); }
	int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	void M(int u, int v) {
		u = F(u); v = F(v);
		if (u == v) return;
		f[v] = u; --cc;
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;
	DSU dsu(n);
	for (int a, b, i = 0; i < m; ++i) {
		cin >> a >> b;
		dsu.M(a, b);
	}
	int p = m - n + dsu.cc;

	const int MOD = 1e9 + 7;
	int ans = 1, x = 2;
	while(p) {
		if (p & 1) ans = (long long) ans * x % MOD;
		x = (long long) x * x % MOD;
		p >>= 1;
	}
	cout << ans << '\n';

	return 0;
}
