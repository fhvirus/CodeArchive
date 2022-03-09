#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll;

ll gcd(ll u, ll v) {
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            unsigned int t = v;
            v = u;
            u = t;
        }
        v = v - u;
    } while (v != 0);
    return u << shift;
}

const int kN = 100001;
const int kL = 17;
int N, M;
vector<int> adj[kN];

int anc[kL][kN], dep[kN];
ll dp[kN], siz[kN], dp_root[kN];
void dfs(int u, int p) {
	anc[0][u] = p;
	for (const int& v: adj[u])
		if (v != p) {
			dep[v] = dep[u] + 1;
			dfs(v, u);
			siz[u] += siz[v];
			dp[u] += dp[v];
		}
	dp[u] += siz[u];
	siz[u] += 1;
}
void move(int u, int v) {
	siz[u] -= siz[v];
	dp[u] -= siz[v] + dp[v];
	dp[v] += siz[u] + dp[u];
	siz[v] += siz[u];
}
void reroot(int u, int p) {
	dp_root[u] = dp[u];
	for (const int& v: adj[u])
		if (v != p) {
			move(u, v);
			reroot(v, u);
			move(v, u);
		}
}
int getLCA(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int d = dep[u] - dep[v], l = 0; l < kL; ++l)
		if (d >> l & 1) u = anc[l][u];
	if (u == v) return u;
	for (int l = kL - 1; l >= 0; --l)
		if (anc[l][u] != anc[l][v]) {
			u = anc[l][u];
			v = anc[l][v];
		}
	return anc[0][u];
}
void print(ll a, ll b) {
	ll g = __gcd(a, b);
	cout << a / g << '/' << b / g << '\n';
}

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int a, b, i = 1; i < N; ++i) {
		cin >> a >> b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	dfs(1, 1);
	for (int l = 1; l < kL; ++l)
		for (int i = 1; i <= N; ++i)
			anc[l][i] = anc[l - 1][anc[l - 1][i]];

	reroot(1, 1);

	for (int p, q, i = 0; i < M; ++i) {
		cin >> p >> q;
		int lca = getLCA(p, q);
		int dis = dep[p] + dep[q] - 2 * dep[lca] + 1;
		if (lca != p and lca != q) {
			ll a = dp[p] * siz[q] + dp[q] * siz[p];
			ll b = siz[p] * siz[q];
			a += b * dis;
			print(a, b);
		} else {
			if (lca != p) swap(p, q);
			int s = q;
			for (int d = dep[q] - dep[p] - 1, l = 0; l < kL; ++l)
				if (d >> l & 1) s = anc[l][s];
			ll dpp = dp_root[p] - dp[s] - siz[s];
			ll sizp = N - siz[s];
			ll a = dpp * siz[q] + dp[q] * sizp;
			ll b = sizp * siz[q];
			a += b * dis;
			print(a, b);
		}
	}

	return 0;
}
