#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


struct Dinic {
	struct E { int v, r; ll c, oc; };
	int n;
	vi le, it, q;
	vector<vector<E>> adj;
	Dinic(int n): n(n), le(n), it(n), q(n), adj(n) {}
	void add(int u, int v, ll c, ll rc = 0) {
		adj[u].push_back({v, sz(adj[v]), c, c});
		adj[v].push_back({u, sz(adj[u]) - 1, rc, rc});
	}
	ll dfs(int u, int t, ll f) {
		if (u == t || !f) return f;
		for (int &i = it[u]; i < sz(adj[u]); ++i) {
			auto &[v, r, c, oc] = adj[u][i];
			if (le[v] == le[u] + 1)
				if (ll p = dfs(v, t, min(f, c)))
					return c -= p, adj[v][r].c += p, p;
		}
		return 0;
	}
	ll flow(int s, int t) {
		ll res = 0; q[0] = s;
		do {
			le = it = vi(sz(q));
			int qi = 0, qe = le[s] = 1;
			while (qi < qe && !le[t]) {
				int u = q[qi++];
				for (auto [v, r, c, oc]: adj[u])
          if (!le[v] && c)
						q[qe++] = v, le[v] = le[u] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) res += p;
		} while (le[t]);
		return res;
	}
	bool inSCut(int u) { return le[u] != 0; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  Dinic din(2 * n + 2);
  rep (i, 0, n) {
    string s;
    cin >> s;
    rep (j, 0, n) if (s[j] == 'o')
      din.add(i, j + n, 1);
  }
  rep (i, 0, n) din.add(2 * n, i, 1);
  rep (j, 0, n) din.add(j + n, 2 * n + 1, 1);

  cout << din.flow(2 * n, 2 * n + 1) << '\n';
  rep (d, 0, 2) rep (i, 0, n)
    if (din.inSCut(i + n * d) == d)
      cout << d + 1 << ' ' << i + 1 << '\n';

  return 0;
}
