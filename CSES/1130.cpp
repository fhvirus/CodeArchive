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

  int n;
  cin >> n;

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans = 0;
  function<int(int, int)> dfs = [&](int u, int p) {
    int cnt = 0;
    for (int v : adj[u]) if (v != p)
      cnt += dfs(v, u);
    if (cnt > 0) ans += 1;
    return cnt == 0;
  };

  dfs(1, 1);

  cout << ans << '\n';
}
