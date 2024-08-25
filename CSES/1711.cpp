#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Dinic {
  struct E { int v, c, r, oc; };
  vector<vector<E>> adj;
  void add(int u, int v, int c) {
    adj[u].push_back({v, c, sz(adj[v]), c});
    adj[v].push_back({u, 0, sz(adj[u]) - 1, 0});
  }
  vi le, it, q;
  Dinic(int n) : adj(n), le(n), it(n), q(n) {}
  int dfs(int u, int t, int f) {
    if (u == t or f == 0) return f;
    for (int &i = it[u]; i < sz(adj[u]); ++i) {
      auto &[v, c, r, oc] = adj[u][i];
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
        for (auto [v, c, r, oc] : adj[u])
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

  int n, m;
  cin >> n >> m;

  Dinic din(1 + n);
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    din.add(a, b, 1);
  }

  int cnt = din.flow(1, n);
  cout << cnt << '\n';

  while (cnt --> 0) {
    vi ans;
    for (int u = 1; u != n; ) {
      ans.push_back(u);
      for (auto &[v, c, r, oc] : din.adj[u]) {
        if (max(oc - c, 0) == 0) continue;
        u = v;
        c = oc;
        break;
      }
    }
    cout << sz(ans) + 1 << '\n';
    for (int i : ans) cout << i << ' ';
    cout << n << '\n';
  }
}
