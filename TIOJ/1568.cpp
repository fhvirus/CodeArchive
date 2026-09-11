#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, V;
  cin >> n >> V;

  vector<int64_t> c(n + 1);
  for (int i = 1; i <= n; ++i) cin >> c[i];

  int en = 0;
  vector<int> to(2 * (n - 1), -1), hd(n + 1, -1), nxt(2 * (n - 1), -1);
  const auto add = [&](int u, int v) {
    to[en] = v; nxt[en] = hd[u]; hd[u] = en++; };
  for (int x, y, i = 1; i < n; ++i) {
    cin >> x >> y;
    add(x, y), add(y, x);
  }

  vector<int> par(n + 1), f(n + 1); f[0] = V;
  for (int i = 0, t = 1; i < n; ++i) {
    int u = f[i];
    for (int e = hd[u]; e != -1; e = nxt[e]) {
      int v = to[e];
      if (par[v] == 0) par[v] = u, f[t++] = v;
    }
  }

  ranges::fill(f, -1);
  const auto find = [&](const auto& self, int u) -> int {
    return f[u] < 0 ? u : f[u] = self(self, f[u]); };

  struct data {
    int u, s; int64_t c;
    bool operator < (const data& o) const { // u does not go before v
      return s * o.c > o.s * c; }
  };
  vector<data> container; container.reserve(n);
  priority_queue<data, vector<data>> pq(less<data>(), move(container));
  for (int i = 1; i <= n; ++i) if (i != V)
    pq.push({i, -f[i], c[i]});

  int64_t ans = accumulate(begin(c), end(c), 0l) - c[V];
  while (not empty(pq)) {
    auto [u, us, uc] = pq.top(); pq.pop();
    if (us != -f[u] or uc != c[u]) continue;
    int p = find(find, par[u]);
    ans += c[u] * -f[p];
    c[p] += c[u];
    f[p] += f[u];
    f[u] = p;
    if (p != V) pq.push({p, -f[p], c[p]});
  }

  cout << ans << '\n';

  return 0;
}
