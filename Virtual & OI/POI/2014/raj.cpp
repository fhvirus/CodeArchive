#include <bits/stdc++.h>
using namespace std;

struct DSU {
	int n, s; vector<int> f;
	DSU (int _n) : n(_n), s(n), f(n + 1) { iota(begin(f), end(f), 0); }
	int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	void M(int u, int v) {
		u = F(u); v = F(v);
		if (u == v) return;
		f[v] = u;
		--s;
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, m; cin >> n >> m;
	vector<vector<int>> adj(n + 2);
	vector<int> indeg(n + 2, 0);
	for (int u, v, i = 0; i < m; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
		++indeg[v];
	} 
	for (int i = 1; i <= n; ++i) {
		adj[0].push_back(i);
		adj[i].push_back(n + 1);
		++indeg[i]; ++indeg[n + 1];
	}

	queue<int> q; q.push(0);
	vector<int> mxd(n + 2, 0);
	vector<int> topo;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		topo.push_back(u);
		for (int &v: adj[u]) {
			mxd[v] = max(mxd[v], mxd[u] + 1);
			--indeg[v];
			if (indeg[v] == 0)
				q.push(v);
		}
	}

	vector<int> red(n + 2, 0);
	vector<int> pos(n + 2);
	for (int i = n + 1; i >= 0; --i) {
		int u = topo[i];
		pos[u] = i;
		for (int &v: adj[u])
			red[u] = max(red[u], red[v] + 1);
	}

	vector<vector<pair<int, int>>> bkt(n + 2);
	for (int u = 0; u <= n + 1; ++u)
		for (int &v: adj[u])
			bkt[mxd[u] + 1 + red[v]].emplace_back(pos[u] + 1, pos[v]);

	DSU dsu(n + 1);
	for (int len = n + 1, lst = 1; len >= 0; --len) {
		for (auto [u, v]: bkt[len]) {
			if (u >= v) continue;
			u = dsu.F(u);
			v = dsu.F(v);
			while (u != v) {
				dsu.M(u + 1, u);
				u = dsu.F(u);
			}
		}
		if (dsu.F(1) == n + 1) {
			int u = topo[lst];
			cout << u << ' ' << len - 2 << '\n';
			return 0;
		} else lst = dsu.F(1);
	}

	return 0;
}
