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

  int n, k1, k2;
  cin >> n >> k1 >> k2;

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  ll ans = 0;
  function<void(vi&, vi&, int, int)> dfs = [&](vi &cnt, vi &pre, int u, int p) {
    for (int v : adj[u]) if (v != p) {
      vi sub(1, 1), sub_pre(1, 1);
      dfs(sub, sub_pre, v, u);
      sub.push_back(0);
      sub_pre.push_back(sub_pre.back());
      if (sz(cnt) < sz(sub)) swap(cnt, sub), swap(pre, sub_pre);
      for (int i = 0; i <= k2 and i < sz(sub); ++i) {
        int p1 = k1 - i, p2 = k2 - i + 1;
        ll sum = (p1 >= sz(cnt) ? 0 : pre[sz(cnt) - 1 - max(0, p1)])
          - (p2 >= sz(cnt) ? 0 : pre[sz(cnt) - 1 - max(0, p2)]);
        ans += sum * sub[sz(sub) - 1 - i];
      }
      rep (i, 0, sz(sub)) cnt[sz(cnt) - 1 - i] += sub[sz(sub) - 1 - i];
      rep (i, sz(cnt) - sz(sub), sz(cnt)) pre[i] = (i > 0 ? pre[i - 1] : 0) + cnt[i];
    }
  };
  vi cnt(1, 1), pre(1, 1);
  dfs(cnt, pre, 1, 1);
  
  cout << ans << '\n';
}
