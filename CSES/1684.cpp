#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct TwoSat {
  vector<vi> adj;
  vi ans;
  TwoSat(int n = 0) : adj(n * 2) {}
  void either(int u, int v) {
    // ~u == -u - 1
    // => -1 - 2 * ~u = -2 * -u + 1 = 2 * u + 1
    // 2 * u + 0/1: u is 0/1
    u = max(2 * u, -1 - 2 * u);
    v = max(2 * v, -1 - 2 * v);
    adj[u].push_back(v ^ 1);
    adj[v].push_back(u ^ 1);
  }
  vi val, con, stk; int toki = 0;
  int dfs(int u) {
    int low = val[u] = ++toki, x;
    stk.push_back(u);
    for (int v : adj[u]) if (not con[v])
      low = min(low, val[v] ?: dfs(v));
    if (low == val[u]) do {
      x = stk.back(); stk.pop_back();
      con[x] = low;
      if (ans[x >> 1] == -1)
        ans[x >> 1] = x & 1;
    } while (x != u);
    return val[u] = low;
  }
  bool solve() {
    ans.assign(sz(adj) / 2, -1);
    val = con = vi(sz(adj), 0);
    rep (i, 0, sz(adj)) if (not con[i]) dfs(i);
    rep (i, 0, sz(adj)) if (con[i] == con[i ^ 1]) return false;
    return true;
  }
};

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  TwoSat ts(m);
  for (int u, v, i = 0; i < n; ++i) {
    char a, b;
    cin >> a >> u >> b >> v;
    u -= 1, v -= 1;
    if (a == '-') u = ~u;
    if (b == '-') v = ~v;
    ts.either(u, v);
  }

  if (not ts.solve())
    return cout << "IMPOSSIBLE\n", 0;

  rep (i, 0, m)
    cout << "-+"[ts.ans[i]] << " \n"[i == m - 1];
}
