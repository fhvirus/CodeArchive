#include <bits/stdc++.h>
using namespace std;

const int kN = 200002;
const int inf = 1e9 + 7;

int n;
vector<int> adj[kN];

int f[kN][3], g[kN][2], h[kN][2];
int dp[3][3], sc[kN][3][3];

void chmin(int &a, int b) { if (a > b) a = b; }

void dfs(int u, int p) {
	h[u][0] = 1; h[u][1] = 2;
	for (int i: {0, 1, 2})
		f[u][i] = inf;

	for (int i: {0, 1, 2})
		for (int j: {0, 1, 2})
			sc[u][i][j] = inf;

	sc[u][0][0] = 0;
	for (const int& v: adj[u]) {
		if (v == p) continue;
		dfs(v, u);

		int t = min({h[v][0], h[v][1], g[v][0]});
		for (int i: {0, 1, 2}) chmin(t, f[v][i]);
		h[u][0] += t;
		h[u][1] += min(t, g[v][1]);

		for (int i: {0, 1, 2})
			for (int j: {0, 1, 2})
				dp[i][j] = inf;

		for (int i: {0, 1, 2}) {
			for (int j: {0, 1, 2}) {
				for (int k: {0, 1, 2})
					chmin(dp[i][max(j, 2 - k)], sc[u][i][j] + f[v][k]);
				for (int k: {0, 1})
					chmin(dp[min(i + k + 1, 2)][j], sc[u][i][j] + h[v][k]);
			}
		}

		for (int i: {0, 1, 2})
			for (int j: {0, 1, 2})
				sc[u][i][j] = dp[i][j];
	}

	for (int i: {0, 1, 2})
		for (int j: {0, 1, 2})
			if (j <= i) chmin(f[u][i], sc[u][i][j]);

	g[u][0] = min(sc[u][0][1], sc[u][1][2]);
	g[u][1] = sc[u][0][2];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;

	for (int a, b, i = 1; i < n; ++i) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(1, 1);

	int ans = min(h[1][0], h[1][1]);
	for (int i: {0, 1, 2})
		ans = min(ans, f[1][i]);

	cout << ans << '\n';

	return 0;
}
