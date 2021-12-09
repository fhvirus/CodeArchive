// baluteshih orz
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int sub(int u, int v, int MOD) {
	u -= v;
	u += MOD & (u >> 31);
	return u;
}

const int kN = 200002;
int n, q, t[kN];
int indeg[kN];
vector<int> adj[kN];

int root[kN], in[kN], ou[kN], dep[kN], tot;
void dfs(int u, int r) {
	root[u] = r;
	in[u] = ++tot;
	for (int &v: adj[u]) {
		dep[v] = dep[u] + 1;
		dfs(v, r);
	}
	ou[u] = tot;
}

int cyc[kN], pos[kN], siz[kN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> t[i];

	for (int i = 1; i <= n; ++i)
		++indeg[t[i]];

	queue<int> kyu;
	for (int i = 1; i <= n; ++i)
		if (indeg[i] == 0) kyu.emplace(i);
	while (!kyu.empty()) {
		int u = kyu.front(); kyu.pop();
		--indeg[t[u]];
		adj[t[u]].emplace_back(u);
		if (indeg[t[u]] == 0)
			kyu.emplace(t[u]);
	}

	for (int i = 1; i <= n; ++i)
		if (indeg[i] == 1) dfs(i, i);

	for (int c = 0, p, i = 1; i <= n; ++i)
		if (indeg[i] == 1 and cyc[i] == 0) {
			++c; p = 0;
			for (int u = i; cyc[u] == 0; u = t[u]) {
				cyc[u] = c;
				pos[u] = p++;
			}
			siz[c] = p;
		}

	for (int a, b, i = 0; i < q; ++i) {
		cin >> a >> b;
		if (cyc[root[a]] != cyc[root[b]])
			cout << -1 << '\n';
		else if (cyc[a] == 0 and cyc[b] == 0)
			cout << (in[b] <= in[a] and ou[a] <= ou[b] ?
				dep[a] - dep[b] : -1) << '\n';
		else
			cout << (cyc[b] == 0 ? -1 :
				dep[a] + sub(pos[b], pos[root[a]], siz[cyc[b]])) << '\n';
	}

	return 0;
}
