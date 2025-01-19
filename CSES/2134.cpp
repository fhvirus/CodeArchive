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
  vi val;
  Seguki(vi v) : n(sz(v)), val(2 * n) {
    rep (i, 0, n) val[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      val[i] = max(val[i * 2], val[i * 2 + 1]);
  }
  void modify(int p, int v) {
    for (val[p += n] = v; p >>= 1; )
      val[p] = max(val[p * 2], val[p * 2 + 1]);
  }
  int query(int l, int r) {
    int res = INT_MIN;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = max(res, val[l++]);
      if (r & 1) res = max(res, val[--r]);
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

  vi dep(n + 1), par(n + 1), siz(n + 1, 1), in(n + 1), out(n + 1), head(n + 1), val(n);
  int toki = 0;
  const function<void(int)> dfs1 = [&](int u) {
    for (int &v : adj[u]) {
      adj[v].erase(find(all(adj[v]), u));
      dep[v] = dep[u] + 1;
      par[v] = u;
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[adj[u][0]])
        swap(v, adj[u][0]);
    }
  };
  const function<void(int)> dfs2 = [&](int u) {
    in[u] = toki++;
    for (int v : adj[u]) {
      head[v] = (v == adj[u][0] ? head[u] : v);
      dfs2(v);
    }
    out[u] = toki;
  };
  dfs1(1);
  head[1] = 1;
  dfs2(1);

  rep (i, 1, n + 1) val[in[i]] = v[i];
  Seguki sgk(val);
  for (int t, a, b; q--; ) {
    cin >> t >> a >> b;
    if (t == 1) sgk.modify(in[a], b);
    else {
      int res = INT_MIN;
      while (head[a] != head[b]) {
        if (dep[head[a]] < dep[head[b]]) swap(a, b);
        res = max(res, sgk.query(in[head[a]], in[a] + 1));
        a = par[head[a]];
      }
      if (dep[a] > dep[b]) swap(a, b);
      res = max(res, sgk.query(in[a], in[b] + 1));
      cout << res << ' ';
    }
  }
}
