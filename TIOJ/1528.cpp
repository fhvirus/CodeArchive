#include <bits/stdc++.h>
using namespace std;

struct DSU {
  vector<int> a;
  DSU (int n) : a(n, -1) {}
  int find(int u) { return a[u] < 0 ? u : a[u] = find(a[u]); }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (a[u] > a[v]) swap(u, v);
    return a[u] += exchange(a[v], u), true;
  }
  int size(int u) { return -a[find(u)]; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  const int en = m - (n - 1);

  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) cin >> a[i];

  vector<pair<int, int>> es;
  vector<int> par(n + 1), ord;
  {
    DSU dsu(n + 1);
    vector adj(n + 1, vector<int>());
    for (int u, v, i = 0; i < m; ++i) {
      cin >> u >> v;
      if (dsu.join(u, v)) {
        adj[u].push_back(v);
        adj[v].push_back(u);
      } else es.emplace_back(u, v);
    }
    ord.push_back(1);
    for (int i = 0; i < n; ++i) {
      int u = ord[i];
      for (int v : adj[u]) if (v != par[u])
        par[v] = u, ord.push_back(v);
    }
    ranges::reverse(ord);
  }

  int64_t ans = 0;

  const int64_t INF = LLONG_MAX / 2;
  vector<int> pick(en, 0);
  vector<array<int64_t, 2>> dp(n + 1);
  while (true) {
    for (int i = 1; i <= n; ++i) dp[i][0] = dp[i][1] = 0;
    for (int e = 0; e < en; ++e) {
      auto [u, v] = es[e];
      dp[u][(pick[e] & 1) == 0] = -INF;
      dp[v][(pick[e] & 2) == 0] = -INF;
    }

    bool bad = false;
    for (int u : ord) {
      if (dp[u][0] < 0 and dp[u][1] < 0) { bad = true; break; }
      dp[u][1] += a[u];
      dp[par[u]][0] += max(dp[u][0], dp[u][1]);
      if (dp[u][0] >= 0) dp[par[u]][1] += dp[u][0];
    }

    if (not bad) ans = max({ans, dp[1][0], dp[1][1]});

    int carry = 1;
    for (int i = 0; i < en and carry; ++i) {
      pick[i] += carry;
      carry = pick[i] / 3;
      pick[i] %= 3;
    }
    if (carry) break;
  }

  cout << ans << '\n';

  return 0;
}
