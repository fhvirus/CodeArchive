// willychan orz
#include <bits/stdc++.h>
using namespace std;

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

  {
    vector<Edge> need; need.reserve(M);
    for (auto [u, v, w] : es)
      if (not cut.count(u * (N + 1) + v))
        need.push_back({u, v, w});
      else cut[u * (N + 1) + v] = w;
    swap(es, need);
  }

  vector<int> par(N + 1), siz(N + 1), cost(N + 1);
  const auto build = [&]() {
    ranges::sort(es, [](auto a, auto b) { return a.w < b.w; });
    vector<Edge> need; need.reserve(N - 1);
    ranges::fill(par, -1); ranges::fill(siz, 1);
    for (auto [u, v, w] : es) {
      int a = u, b = v;
      while (par[a] >= 0) a = par[a];
      while (par[b] >= 0) b = par[b];
      if (a == b) continue;
      need.push_back({u, v, w});
      if (siz[a] < siz[b]) swap(a, b);
      par[b] = a, siz[a] += siz[b], cost[b] = w;
    }
    swap(es, need);
  };
  const auto query = [&](int p, int q) {
    int ans = 0;
    while (p != q) {
      if (siz[p] > siz[q]) swap(p, q);
      ans = max(ans, cost[p]);
      p = par[p];
    }
    return ans;
  };

  bool good = false;
  vector<int> ans;
  for (auto [p, q, t] : qs | views::reverse) {
    if (t == 2) {
      good = false;
      es.push_back({p, q, cut[p * (N + 1) + q]});
    } else {
      if (not good) { build(); good = true; }
      ans.push_back(query(p, q));
    }
  }

  for (int i : ans | views::reverse)
    cout << i << '\n';

  return 0;
}
