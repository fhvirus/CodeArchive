#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  int l = __lg(n) + 1;

  vector<vi> e(l, vi(n + 1));
  rep (i, 2, n + 1) cin >> e[0][i];
  rep (i, 1, l) rep(j, 1, n + 1)
    e[i][j] = e[i - 1][e[i - 1][j]];

  vi dep(n + 1), ord;
  rep (i, 2, n + 1) dep[e[0][i]] += 1;
  rep (i, 1, n + 1) if (dep[i] == 0) ord.push_back(i);
  rep (i, 0, sz(ord)) {
    int p = e[0][ord[i]];
    if (--dep[p] == 0)
      ord.push_back(p);
  }
  reverse(all(ord));
  for (int i : ord) dep[i] = dep[e[0][i]] + 1;

  const auto lca = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) swap(u, v);
    for (int d = dep[u] - dep[v], i = 0; i < l; ++i)
      if (d >> i & 1) u = e[i][u];
    if (u == v) return u;
    for (int i = l - 1; i >= 0; --i) {
      int a = e[i][u], b = e[i][v];
      if (a != b) u = a, v = b;
    }
    return e[0][u];
  };

  for (int a, b; q--; ) {
    cin >> a >> b;
    cout << lca(a, b) << '\n';
  }
}
