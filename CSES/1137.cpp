#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Seguki {
  int n;
  vector<ll> val;
  Seguki(vi v) : n(sz(v)), val(2 * n) {
    rep (i, 0, n) val[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      val[i] = val[i * 2] + val[i * 2 + 1];
  }
  void modify(int p, int v) {
    for (val[p += n] = v; p >>= 1; )
      val[p] = val[p * 2] + val[p * 2 + 1];
  }
  ll query(int l, int r) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res += val[l++];
      if (r & 1) res += val[--r];
    }
    return res;
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

  vi in(n + 1), out(n + 1), val(n);
  int toki = 0;
  const function<void(int, int)> dfs = [&](int u, int p) {
    in[u] = toki++;
    for (int v : adj[u]) if (v != p) dfs(v, u);
    out[u] = toki;
  };
  dfs(1, 0);
  rep (i, 1, n + 1) val[in[i]] = v[i];

  Seguki sgk(val);
  for (int t, s, x; q--; ) {
    cin >> t >> s;
    if (t == 1) {
      cin >> x;
      sgk.modify(in[s], x);
    } else cout << sgk.query(in[s], out[s]) << '\n';
  }
}
