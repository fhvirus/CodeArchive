#include <bits/stdc++.h>
using namespace std;

const int kL = 30, kINF = (1 << kL) - 1;
struct Val {
  array<int, kL> a;
  Val (int x) { ranges::fill(a, kINF); a[__lg(x)] = x; }
  Val operator + (const Val& o) const {
    Val r(kINF);
    for (int i = 0; i < kL; ++i) r.a[i] = min(a[i], o.a[i]);
    return r;
  }
};
struct Seguki {
  int n;
  vector<Val> val;
  Seguki(vector<int> v) : n(int(size(v))), val(n * 2, kINF) {
    for (int i = 0; i < n; ++i) val[i + n] = Val(v[i]);
    for (int i = n - 1; i > 0; --i) val[i] = val[i * 2] + val[i * 2 + 1];
  }
  Val query(int l, int r) {
    Val res(kINF);
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) res = res + val[l++];
      if (r & 1) res = res + val[--r];
    }
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  vector pre(n + 1, array<int64_t, kL> {0});
  for (int i = 0; i < n; ++i) {
    pre[i + 1] = pre[i];
    pre[i + 1][__lg(x[i])] += x[i];
  }
  Seguki sgk(x);

  for (int a, b; q --> 0; ) {
    cin >> a >> b; a -= 1;
    int64_t sum = 0, ans = -1;
    auto mnv = sgk.query(a, b).a;
    for (int l = 0; l < kL; ++l) {
      int rb = (1 << (l + 1)) - 1;
      if (sum + 1 < min(rb, mnv[l])) {
        ans = sum + 1;
        break;
      }
      sum += pre[b][l] - pre[a][l];
    }
    cout << (ans == -1 ? sum + 1 : ans) << '\n';
  }

  return 0;
}
