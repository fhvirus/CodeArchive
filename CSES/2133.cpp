#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct DSU {
  vi f; vector<pii> stk;
  DSU (int n) : f(n, -1) {}
  void reset() { fill(all(f), -1); }
  int find(int u) { return f[u] < 0 ? u : find(f[u]); }
  int time() { return sz(stk); }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (f[u] > f[v]) swap(u, v);
    stk.emplace_back(u, f[u]);
    stk.emplace_back(v, f[v]);
    f[u] += exchange(f[v], u);
    return true;
  }
  void rollback(int t) {
    for (int i = time(); i --> t; )
      f[stk[i].first] = stk[i].second;
    stk.resize(t);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  typedef tuple<int, int, int, int> quad;

  int n, m, k;
  cin >> n >> m >> k;

  vector<quad> es;
  map<pii, int> mp;
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    if (u > v) swap(u, v);
    mp[pii(u, v)] = 0;
  }
  for (int t, u, v, i = 1; i <= k; ++i) {
    cin >> t >> u >> v;
    if (u > v) swap(u, v);
    if (t == 1)
      mp[pii(u, v)] = i;
    else {
      auto it = mp.find(pii(u, v));
      es.emplace_back(it->second, i, u, v);
      mp.erase(it);
    }
  }
  for (auto [e, t] : mp)
    es.emplace_back(t, k + 1, e.first, e.second);

  DSU dsu(n + 1);
  vi ans(k + 1);
  const auto dfs = [&](const auto &dfs, int tl, int tr, const vector<quad> &qs, int cc) -> void {
    int dsut = dsu.time();
    if (tl + 1 == tr) {
      for (auto [ql, qr, u, v] : qs)
        cc -= dsu.join(u, v);
      ans[tl] = cc;
      dsu.rollback(dsut);
      return;
    }
    int mid = (tl + tr) / 2;
    vector<quad> lq, rq;
    for (auto [ql, qr, u, v] : qs) {
      if (ql <= tl and tr <= qr)
        cc -= dsu.join(u, v);
      else {
        if (ql < mid) lq.emplace_back(ql, qr, u, v);
        if (mid < qr) rq.emplace_back(ql, qr, u, v);
      }
    }
    dfs(dfs, tl, mid, lq, cc);
    dfs(dfs, mid, tr, rq, cc);
    dsu.rollback(dsut);
    return;
  };

  dfs(dfs, 0, k + 1, es, n);

  rep (i, 0, k + 1)
    cout << ans[i] << " \n"[i == k];

  return 0;
}
