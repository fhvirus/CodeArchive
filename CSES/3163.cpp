#include <bits/stdc++.h>
using namespace std;

struct BIT {
  vector<int> val;
  BIT (int n) : val(n) {}
  void modify(int p, int v) {
    for (; p < int(size(val)); p += p & -p)
      val[p] += v;
  }
  int query(int p) {
    int r = 0;
    for (; p > 0; p -= p & -p)
      r += val[p];
    return r;
  }
  int query(int l, int r) { return query(r) - query(l - 1); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<tuple<int, int, int, int>> qs;
  for (int x, i = 1; i <= n; ++i) {
    cin >> x;
    qs.emplace_back(x, 0, 0, i);
  }
  for (int a, b, c, d, i = 0; i < q; ++i) {
    cin >> a >> b >> c >> d;
    qs.emplace_back(c, ~i, a, b);
    qs.emplace_back(d, i, a, b);
  }

  ranges::sort(qs);

  BIT bit(n + 1);
  vector<int> ans(q);
  for (auto [_, id, l, r] : qs) {
    if (l == 0) bit.modify(r, 1);
    else if (id < 0) ans[~id] -= bit.query(l, r);
    else ans[id] += bit.query(l, r);
  }

  for (int i : ans) cout << i << '\n';
  
  return 0;
}
