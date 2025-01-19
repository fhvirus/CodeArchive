#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,popcnt")
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<vi> adj(n);
  vi deg(n);
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    adj[v - 1].push_back(u - 1);
    deg[u - 1] += 1;
  }

  vi ord;
  rep (i, 0, n) if (deg[i] == 0) ord.push_back(i);
  rep (i, 0, n) {
    for (int v : adj[ord[i]])
      if (--deg[v] == 0)
        ord.push_back(v);
  }

  vi ans(n);
  vector<bitset<50000>> dp(n);
  for (int u : ord) {
    dp[u][u] = 1;
    ans[u] += dp[u].count();
    for (int v : adj[u]) dp[v] = dp[v] | dp[u];
  }

  rep (i, 0, n) cout << ans[i] << " \n"[i == n - 1];

  return 0;
}
