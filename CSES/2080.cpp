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

  int n, k;
  cin >> n >> k;

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  ll ans = 0;
  function<vi(int, int)> dfs = [&](int u, int p) {
    vi cnt(1, 1);
    for (int v : adj[u]) if (v != p) {
      auto sub = dfs(v, u);
      sub.push_back(0);
      if (sz(cnt) < sz(sub)) swap(cnt, sub);
      rep (i, 0, min(k + 1, sz(sub))) if (k - i < sz(cnt))
        ans += (ll) sub[sz(sub) - 1 - i] * cnt[sz(cnt) - 1 - (k - i)];
      rep (i, 0, sz(sub)) cnt[sz(cnt) - 1 - i] += sub[sz(sub) - 1 - i];
    }
    return cnt;
  };
  dfs(1, 1);
  
  cout << ans << '\n';
}
