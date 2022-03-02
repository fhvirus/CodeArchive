#include <bits/stdc++.h>
using namespace std;

const int kN = 50005;
int n, m, q;
vector<int> adj[kN];

int pre[kN], low[kN], tot;
int ins[kN], stk[kN], top;
int scc[kN], cnt;

void dfs(int u) {
	pre[u] = low[u] = ++tot;
	ins[u] = 1; stk[++top] = u;
	for (int &v: adj[u]) {
		if (pre[v] == 0) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (ins[v])
			low[u] = min(low[u], pre[v]);
	}
	if (low[u] == pre[u]) {
		++cnt;
		int v;
		do {
			v = stk[top--];
			ins[v] = 0;
			scc[v] = cnt;
		} while (v != u);
	}
}

vector<int> bdj[kN];
int ind[kN], tps[kN];

bitset<kN> dp[kN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m >> q;
	for (int a, b, i = 0; i < m; ++i) {
		cin >> a >> b;
		adj[a].push_back(b);
	}

	for (int i = 1; i <= n; ++i)
		if (pre[i] == 0) dfs(i);

	for (int i = 1; i <= n; ++i)
		for (int &j: adj[i]) {
			int u = scc[i], v = scc[j];
			if (u == v) continue;
			bdj[u].push_back(v);
			ind[v]++;
		}

	queue<int> qu;
	for (int i = 1; i <= cnt; ++i)
		if (ind[i] == 0) qu.push(i);

	int tmp = cnt;
	while (!qu.empty()) {
		int u = qu.front(); qu.pop();
		tps[tmp--] = u;
		for (int &v: bdj[u])
			if ((--ind[v]) == 0)
				qu.push(v);
	}

	for (int i = 1; i <= cnt; ++i) {
		int u = tps[i];
		dp[u][u] = 1;
		for (int &v: bdj[u])
			dp[u] |= dp[v];
	}

	for (int a, b, i = 0; i < q; ++i) {
		cin >> a >> b;
		cout << (dp[scc[a]][scc[b]] ? "YES\n" : "NO\n");
	}
	return 0;
}
