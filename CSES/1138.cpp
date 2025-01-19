#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Fenwick {
  vector<ll> val;
  Fenwick(int n) : val(n, 0) {}
  void modify(int p, ll v) {
    for (; p < sz(val); p += p & -p)
      val[p] += v;
  }
  ll query(int p) {
    ll v = 0;
    for (; p > 0; p -= p & -p)
      v += val[p];
    return v;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vi v(n + 1);
  rep (i, 1, n + 1) cin >> v[i];

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vi in(n + 1), out(n + 1);
  int toki = 1;
  const function<void(int, int)> dfs = [&](int u, int p) {
    in[u] = toki++;
    for (int v : adj[u]) if (v != p) dfs(v, u);
    out[u] = toki;
  };
  dfs(1, 0);

  Fenwick fen(n + 1);
  rep (i, 1, n + 1) fen.modify(in[i], v[i]), fen.modify(out[i], -v[i]);
  for (int t, s, x; q--; ) {
    cin >> t >> s;
    if (t == 1) {
      cin >> x;
      fen.modify(in[s], x - v[s]);
      fen.modify(out[s], v[s] - x);
      v[s] = x;
    } else cout << fen.query(in[s]) << '\n';
  }
}
