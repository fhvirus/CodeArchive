#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct DSU {
  vi f;
  DSU (int n) : f(n, -1) {}
  void reset() { fill(all(f), -1); }
  int find(int u) { return f[u] < 0 ? u : f[u] = find(f[u]); }
  void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (f[u] > f[v]) swap(u, v);
    f[u] += exchange(f[v], u);
  }
  bool same(int u, int v) { return find(u) == find(v); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, q;
  cin >> n >> m >> q;

  vector<pii> es(m + 1), qs(q);
  rep (i, 1, m + 1)
    cin >> es[i].first >> es[i].second;
  for (auto &[u, v] : qs)
    cin >> u >> v;
  vi ans(q, -1);

  DSU dsu(n + 1);
  int ptr = 0;
  queue<tuple<int, int, vi>> que;
  vi tmp(q); iota(all(tmp), 0);
  que.emplace(0, m + 2, tmp);

  while (not que.empty()) {
    auto [l, r, qi] = que.front(); que.pop();
    if (l + 1 == r) {
      for (int i : qi)
        ans[i] = l;
      continue;
    }
    int mid = (l + r) / 2;
    for (; ptr < mid; ++ptr)
      dsu.merge(es[ptr].first, es[ptr].second);
    vi ql, qr;
    for (int i : qi) {
      if (dsu.same(qs[i].first, qs[i].second))
        ql.push_back(i);
      else
        qr.push_back(i);
    }
    if (not ql.empty()) que.emplace(l, mid, ql);
    if (not qr.empty()) que.emplace(mid, r, qr);
    if (not que.empty() and get<0>(que.front()) < r) {
      dsu.reset();
      ptr = 0;
    }
  }

  for (int i : ans)
    cout << (i == m + 1 ? -1 : i) << '\n';

  return 0;
}
