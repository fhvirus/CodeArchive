#include <bits/stdc++.h>
using namespace std;

constexpr int INF = INT_MAX / 2;

struct Data {
  int to, neg, pos, two;
  Data (int _to = -1, int _neg = -INF, int _pos = -INF, int _two = -INF) :
    to(_to), neg(_neg), pos(_pos), two(_two) {}
  Data operator + (const Data& o) const {
    return Data(o.to, max(neg, o.neg), max(pos, o.pos),
        max({two, o.two, neg + o.pos + 2}));
  }
};
template <int kS> struct MaxS {
  array<int, kS> val, id;
  int s = 0;
  void put(int v, int i) {
    if (s == kS and val[kS - 1] >= v) return;
    for (int j = 0; j < s; ++j) if (val[j] < v)
      swap(val[j], v), swap(id[j], i);
    if (s < kS) { val[s] = v, id[s] = i; ++s; }
  }
  int get(int a, int b = -1) {
    for (int j = 0; j < s; ++j)
      if (id[j] != a and id[j] != b) return val[j];
    return 0;
  }
  int get2(int a, int b = -1) {
    int sum = 0, cnt = 0;
    for (int j = 0; j < s and cnt < 2; ++j)
      if (id[j] != a and id[j] != b)
        sum += val[j], ++cnt;
    return sum;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> tree(N);
  vector<tuple<int, int, int>> es;
  for (int x, y, w, i = 0; i < M; ++i) {
    cin >> x >> y >> w;
    if (w == 1) {
      tree[x].push_back(y);
      tree[y].push_back(x);
    } else if (N > 2 * w)
      es.emplace_back(x, y, w);
  }

  vector<int> par(N, -1), dep(N);
  vector<MaxS<4>> ch_dep(N);
  vector<MaxS<3>> ch_dia(N);
  const auto max_ch_dia_utom = [&](int u, int a, int b) {
    return max(ch_dep[u].get2(a, b), ch_dia[u].get(a, b)); };
  const auto& dfs1 = [&](const auto& self, int u) -> void {
    for (int i = 0; i < (int)size(tree[u]); ++i) {
      int v = tree[u][i];
      if (v == par[u]) {
        tree[u][i--] = tree[u].back();
        tree[u].pop_back();
        continue;
      }
      par[v] = u, dep[v] = dep[u] + 1;
      self(self, v);
      int v_dep = ch_dep[v].get(u) + 1;
      int v_dia = max(max_ch_dia_utom(v, u, -1), v_dep);
      ch_dep[u].put(v_dep, v);
      ch_dia[u].put(v_dia, v);
    }
  };
  dfs1(dfs1, 0);

  const auto dfs2 = [&](const auto& self, int u) -> void {
    for (int v : tree[u]) {
      int u_dep = ch_dep[u].get(v) + 1;
      int u_dia = max(max_ch_dia_utom(u, v, -1), u_dep);
      ch_dep[v].put(u_dep, u);
      ch_dia[v].put(u_dia, u);
      self(self, v);
    }
  };
  dfs2(dfs2, 0);

  const auto get_data = [&](int u, int v) {
    int d = ch_dep[u].get(v, par[u]);
    return Data(u, d - dep[u], d + dep[u],
        max_ch_dia_utom(u, v, par[u]));
  };

  const int L = __lg(N) + 1;
  vector jmp(L, vector<Data>(N));
  for (int i = 1; i < N; ++i) jmp[0][i] = get_data(par[i], i);
  for (int l = 1; l < L; ++l)
    for (int i = 0; i < N; ++i) {
      int t = jmp[l - 1][i].to;
      if (t != -1)
        jmp[l][i] = jmp[l - 1][i] + jmp[l - 1][t];
    }

  int ans = 2 * N - 2 - max_ch_dia_utom(0, -1, -1);
  for (auto [x, y, w] : es) {
    if (ans <= N - 2 + w) continue;
    if (dep[x] < dep[y]) swap(x, y);
    Data dx = get_data(x, -1), dy(y);
    for (int dd = dep[x] - dep[y] - 1, l = 0; (1 << l) <= dd; ++l)
      if ((dd >> l & 1)) dx = dx + jmp[l][dx.to];
    if (par[dx.to] != y) {
      if (dep[x] > dep[y])
        dx = dx + jmp[0][dx.to];
      dy = get_data(y, -1);
      for (int l = __lg(dep[x]); l >= 0; --l)
        if (jmp[l][dx.to].to != jmp[l][dy.to].to) {
          dx = dx + jmp[l][dx.to];
          dy = dy + jmp[l][dy.to];
        }
    }
    int lca = par[dx.to];
    int lca_one = ch_dep[lca].get(dx.to, dy.to);
    int lca_two = max_ch_dia_utom(lca, dx.to, dy.to);

    // (x -- px) -- (lca) -- (py -- y)
    int len = dep[x] + dx.neg + dep[y] + dy.neg + 2; // 1 0 1
    len = max(len, dep[x] + dx.neg + lca_one + dep[y] - dep[lca] + 2); // 1 1 0
    len = max(len, dep[y] + dy.neg + lca_one + dep[x] - dep[lca] + 2); // 0 1 1
    len = max(len, dep[x] - dep[lca] + dep[y] - dep[lca] +
        max({lca_two, dx.two, dy.two})); // 020 200 002
    ans = min(ans, w + (2 * N - 2) - len);
  }
  cout << ans << '\n';

  return 0;
}
