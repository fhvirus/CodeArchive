#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct SCC {
  vector<vi> adj;
  vi val, con, stk;
  int toki = 0, ncon = 0;
  int dfs(int u) {
    int low = val[u] = ++toki, x;
    stk.push_back(u);
    for (int v : adj[u]) if (con[v] < 0)
      low = min(low, val[v] ?: dfs(v));
    if (low == val[u]) {
      do {
        x = stk.back(); stk.pop_back();
        con[x] = ncon;
      } while (x != u);
      ++ncon;
    }
    return val[u] = low;
  }
  SCC(vector<vi> a) : adj(a), val(sz(a), 0), con(sz(a), -1) {
    rep (i, 0, sz(adj)) if (con[i] < 0) dfs(i); }
};

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vi k(n + 1);
  rep (i, 1, n + 1) cin >> k[i];

  vector<vi> adj(n + 1);
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
  }

  SCC scc(adj);
  int num = scc.ncon;

  vector<vi> nadj(num);
  vi ind(num);
  rep (u, 1, n + 1) for (int v : adj[u])
    if (scc.con[u] != scc.con[v])
      nadj[scc.con[u]].push_back(scc.con[v]),
        ind[scc.con[v]] += 1;

  vector<ll> ksum(num);
  rep (u, 1, n + 1)
    ksum[scc.con[u]] += k[u];

  vector<ll> dp(num);
  queue<int> q;
  rep (i, 0, num) if (ind[i] == 0) q.push(i);
  while (not q.empty()) {
    int u = q.front(); q.pop();
    dp[u] += ksum[u];
    for (int v : nadj[u]) {
      dp[v] = max(dp[v], dp[u]);
      ind[v] -= 1;
      if (ind[v] == 0)
        q.push(v);
    }
  }

  cout << *max_element(all(dp)) << '\n';

}
