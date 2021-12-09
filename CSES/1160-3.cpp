// Ort orz
#include <iostream>
using namespace std;

const int kN = 200002;
const int kL = 18;

int n, q, t[kL][kN], d[kN], vis[kN], ans;
void dfs(int u) {
	vis[u] = true;
	if (!vis[t[0][u]]) dfs(t[0][u]);
	d[u] = d[t[0][u]] + 1;
}
int go(int u, int k) {
	if (k < 0) return u;
	ans += k;
	for (int l = kL - 1; l >= 0; --l)
		if (k >> l & 1) u = t[l][u];
	return u;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> t[0][i];
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
	for (int l = 1; l < kL; ++l)
		for (int i = 1; i <= n; ++i)
			t[l][i] = t[l-1][t[l-1][i]];
	for (int a, b, i = 0; i < q; ++i) {
		cin >> a >> b;
		ans = 0;
		a = go(a, d[a] - d[b]);
		if (a == b) {
			cout << ans << '\n';
			continue;
		}
		a = go(a, d[a]);
		a = go(a, d[a] - d[b]);
		cout << (a == b ? ans : -1) << '\n';
	}

	return 0;
}
