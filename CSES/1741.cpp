#include <bits/stdc++.h>
using namespace std;

struct Val {
  int val, len, sum;
  Val (int l = 0) : val(0), len(l), sum(0) {}
  Val (int v, int l, int s) : val(v), len(l), sum(s) {}
  void upd(int t) { val += t; }
  int operator() () const { return val ? len : sum; }
  Val operator + (const Val& o) const
  { return Val(min(val, o.val), len + o.len, (*this)() + o()); }
};
int bc(int u) { return 2 << __lg(max(u, 2) - 1); }
struct Seguki {
  int n; vector<Val> val;
  Seguki(const vector<Val>& v): n(bc(int(size(v)))), val(n*2) {
    for (int i = 0; i < int(size(v)); ++i) val[i+n] = v[i];
    for (int i = n; --i; ) val[i] = val[i*2] + val[i*2+1];
  }
  void pull(int u)
  { while (u /= 2) val[u].sum = val[u*2]() + val[u*2+1](); }
  void modify(int l, int r, int t) {
    int tl = (l += n), tr = (r += n) - 1;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) val[l++].upd(t);
      if (r & 1) val[--r].upd(t);
    }
    pull(tl); pull(tr);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<tuple<int, int, int, int>> qs;
  vector<int> ys;
  for (int x1, y1, x2, y2, i = 0; i < n; ++i) {
    cin >> x1 >> y1 >> x2 >> y2;
    ys.push_back(y1); ys.push_back(y2);
    qs.emplace_back(x1, y1, y2, 1);
    qs.emplace_back(x2, y1, y2, -1);
  }
  ranges::sort(qs);
  ranges::sort(ys); ys.erase(ranges::unique(ys).begin(), end(ys));
  for (auto &[x, l, r, _] : qs) {
    l = int(ranges::lower_bound(ys, l) - begin(ys));
    r = int(ranges::lower_bound(ys, r) - begin(ys));
  }

  vector<Val> vs;
  for (int i = 1; i < int(size(ys)); ++i)
    vs.emplace_back(ys[i] - ys[i - 1]);
  Seguki sgk(vs);

  int px = get<0>(qs[0]);
  int64_t ans = 0;
  for (auto [x, l, r, t] : qs) {
    if (x != px) ans += sgk.val[1]() * int64_t(x - px);
    px = x;
    sgk.modify(l, r, t);
  }

  cout << ans << '\n';

  return 0;
}
