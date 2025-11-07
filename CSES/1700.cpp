// https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
// instead of depth of the subtree, i use depth of the node
// not sure if the prob. still right but it passed the tests
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
  static const ll mod = 1e9 + 7;
  static mt19937 mt(7122);
  static vector<ll> xs;

  int n;
  cin >> n;

  while (sz(xs) < n) xs.push_back(mt() % mod);

  ll hs = 0;
  rep (t, 0, 2) {
    vector<vi> adj(n + 1);
    for (int u, v, i = 1; i < n; ++i) {
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    const auto dfs = [&](const auto& self, int u, int p, int d) -> ll {
      ll h = 1;
      for (int v : adj[u]) if (v != p)
        h = h * (xs[d] + self(self, v, u, d + 1)) % mod;
      return h;
    };
    hs ^= dfs(dfs, 1, 1, 0);
  }

  cout << (hs == 0 ? "YES\n" : "NO\n");
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;
  while (t --> 0) solve();

  return 0;
}
