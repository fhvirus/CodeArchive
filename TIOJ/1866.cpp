#include <bits/stdc++.h>
using namespace std;

const int kN = 100001;
const int kL = 30;
const int kNode = kL * kN;

int T, n, a[kN];
vector<int> adj[kN];

int ch[kNode][2], root[kN], tot;
int ans[kN];

int newNode(int o) {
	++tot;
	ch[tot][0] = ch[o][0];
	ch[tot][1] = ch[o][1];
	return tot;
}

int insert(int rt, int val) {
	int nn = newNode(rt);
	rt = nn;
	for (int lg = kL - 1; lg >= 0; --lg)
		rt = ch[rt][val >> lg & 1] = newNode(ch[rt][val >> lg & 1]);
	return nn;
}

int query(int rt, int val) {
	int res = 0;
	for (int lg = kL - 1; lg >= 0; --lg)
		if (ch[rt][1 ^ (val >> lg & 1)] != 0) {
			res ^= (1 << lg);
			rt = ch[rt][1 ^ (val >> lg & 1)];
		} else
			rt = ch[rt][val >> lg & 1];
	return res;
}

void dfs(int u, int p, int val, int mxv) {
	int tmp = tot;
	ans[u] = mxv = max(mxv, query(root[p], val));
	root[u] = insert(root[p], val);
	for (const int& v: adj[u]) {
		if (v == p) continue;
		dfs(v, u, val ^ a[v], mxv);
	}
	tot = tmp;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int u, v, i = 1; i < n; ++i) {
		cin >> u >> v;
		adj[u].emplace_back(v);
	}

	root[0] = insert(0, 0);
	dfs(1, 0, a[1], 0);

	for (int i = 1; i <= n; ++i)
		cout << ans[i] << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> T;
	while (T --> 0) solve();

	return 0;
}
