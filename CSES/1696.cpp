#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Dinic {
  struct E { int v, c, r; };
  vector<vector<E>> adj;
  void add(int u, int v, int c, int rc = 0) {
    adj[u].push_back({v, c, sz(adj[v])});
    adj[v].push_back({u, rc, sz(adj[u]) - 1});
  }
  vi le, it, q;
  Dinic(int n) : adj(n), le(n), it(n), q(n) {}
  int dfs(int u, int t, int f) {
    if (u == t or f == 0) return f;
    for (int &i = it[u]; i < sz(adj[u]); ++i) {
      auto &[v, c, r] = adj[u][i];
      if (c > 0 and le[v] == le[u] + 1)
        if (int p = dfs(v, t, min(c, f)); p > 0)
          return c -= p, adj[v][r].c += p, p;
    }
    return 0;
  }
  int flow(int s, int t) {
    int ans = 0; q[0] = s;
    do {
      le = it = vi(sz(q));
      int qi = 0, qe = le[s] = 1;
      while (qi < qe and le[t] == 0) {
        int u = q[qi++];
        for (auto [v, c, r] : adj[u])
          if (c > 0 and le[v] == 0)
            q[qe++] = v, le[v] = le[u] + 1;
      }
      while (int p = dfs(s, t, INT_MAX)) ans += p;
    } while (le[t] != 0);
    return ans;
  }
  bool inSCut(int u) { return le[u] != 0; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, k;
  cin >> n >> m >> k;

  Dinic din(1 + n + m + 1);
  for (int a, b, i = 0; i < k; ++i) {
    cin >> a >> b;
    din.add(a, n + b, 1);
  }
  for (int i = 1; i <= n; ++i) din.add(0, i, 1);
  for (int i = 1; i <= m; ++i) din.add(n + i, n + m + 1, 1);

  cout << din.flow(0, n + m + 1) << '\n';
  for (int u = 1; u <= n; ++u)
    for (auto [v, c, r] : din.adj[u])
      if (c == 0 and v > n) cout << u << ' ' << v - n << '\n';
}
