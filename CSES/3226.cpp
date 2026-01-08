#include <bits/stdc++.h>
using namespace std;

int bc(int u) { return u <= 1 ? 1 : (2 << __lg(u-1)); }
struct Val {
  int64_t val, pre, suf, sum;
  Val(int64_t v = 0) : val(v), pre(v), suf(v), sum(v) {}
  Val(int64_t v, int64_t p, int64_t s, int64_t t) : val(v), pre(p), suf(s), sum(t) {}
  Val operator + (const Val &o) const {
    return Val(max({val, o.val, suf + o.pre}),
        max(pre, sum + o.pre), max(o.suf, suf + o.sum), sum + o.sum); }
};
struct Seguki {
  int n;
  vector<Val> val;
  Seguki(int _n) : n(bc(_n)), val(n * 2) {}
  void modify(int p, Val v) {
    for (val[p += n] = v; p >>= 1; )
      val[p] = val[p * 2] + val[p * 2 + 1];
  }
  Val query(int l, int r) {
    Val rl, rr;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) rl = rl + val[l++];
      if (r & 1) rr = val[--r] + rr;
    }
    return rl + rr;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  Seguki sgk(n);
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    sgk.modify(i, Val(x));
  }
  for (int a, b; q --> 0; ) {
    cin >> a >> b;
    cout << max(0l, sgk.query(a - 1, b).val) << '\n';
  }

  return 0;
}
