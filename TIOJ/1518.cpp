#include <bits/stdc++.h>
using namespace std;

struct DSU {
  vector<int> a;
  DSU (int n) : a(n, -1) {}
  int find(int u) { return a[u] < 0 ? u : a[u] = find(a[u]); }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (a[u] > a[v]) swap(u, v);
    return a[u] += exchange(a[v], u), true;
  }
  int size(int u) { return -a[find(u)]; }
  void reset() { ranges::fill(a, -1); }
};

struct Edge { int u, v, w; };

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, K;
  cin >> N >> M >> K;

  vector<Edge> es(M);
  for (auto &[a, b, c] : es) {
    cin >> a >> b >> c;
    if (a > b) swap(a, b);
  }

  unordered_map<int, int> cut;
  vector<Edge> qs;
  for (int t, p, q, i = 0; i < K; ++i) {
    cin >> t >> p >> q;
    if (p > q) swap(p, q);
    if (t == 2) {
      int id = p * (N + 1) + q;
      if (cut.count(id)) continue;
      cut[id] = INT_MAX;
    }
    qs.push_back({p, q, t});
  }

  ranges::sort(es, [](auto a, auto b) { return a.w < b.w; });

  vector<Edge> need;
  DSU dsu(N + 1);
  for (auto [u, v, w] : es) {
    if (int id = u * (N + 1) + v; cut.count(id)) cut[id] = w;
    else if (dsu.join(u, v)) need.push_back({u, v, w});
  }

  const int L = __lg(N) + 1;
  vector jump(L, vector(N + 1, pair<int, int>(0, 0)));
  vector<int> dep(N + 1), ord;
  bool good = false;
  const auto build = [&]() {
    ranges::sort(need, [](auto a, auto b) { return a.w < b.w; });
    dsu.reset();
    vector adj(N + 1, vector<pair<int, int>>());
    vector<Edge> nxt; nxt.reserve(N - 1);
    for (auto [u, v, w] : need) if (dsu.join(u, v)) {
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
      nxt.push_back({u, v, w});
    }
    swap(nxt, need);
    ranges::fill(dep, -1); ord.clear();
    dep[1] = 0, ord.push_back(1);
    for (int i = 0; i < N; ++i) {
      int u = ord[i];
      for (auto [v, w] : adj[u]) if (dep[v] == -1) {
        jump[0][v] = pair(u, w);
        dep[v] = dep[u] + 1;
        ord.push_back(v);
      }
    }
    for (int l = 1; l < L; ++l)
      for (int i = 1; i <= N; ++i) {
        auto [u, a] = jump[l - 1][i];
        auto [v, b] = jump[l - 1][u];
        jump[l][i] = pair(v, max(a, b));
      }
    good = true;
  };
  const auto query = [&](int p, int q) {
    if (dep[p] < dep[q]) swap(p, q);
    int ans = 0;
    for (int d = dep[p] - dep[q], l = 0; (1 << l) <= d; ++l)
      if (d >> l & 1) {
        auto [u, w] = jump[l][p];
        ans = max(ans, w), p = u;
      }
    if (p == q) return ans;
    for (int l = L - 1; l >= 0; --l) {
      auto [jp, wp] = jump[l][p];
      auto [jq, wq] = jump[l][q];
      if (jp != jq) ans = max({ans, wp, wq}), p = jp, q = jq;
    }
    return max({ans, jump[0][p].second, jump[0][q].second});
  };


  vector<int> ans;
  for (auto [p, q, t] : qs | views::reverse) {
    if (t == 2) {
      int id = p * (N + 1) + q;
      need.push_back({p, q, cut[id]});
      good = false;
    } else {
      if (not good) build();
      ans.push_back(query(p, q));
    }
  }

  for (int i : ans | views::reverse)
    cout << i << '\n';

  return 0;
}
