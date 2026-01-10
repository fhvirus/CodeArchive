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
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> x(n);
  for (int &i : x) cin >> i;
  {
    auto v = x;
    ranges::sort(v);
    v.erase(begin(ranges::unique(v)), end(v));
    for (int &i : x)
      i = int(ranges::lower_bound(v, i) - begin(v)) + 1;
  }

  int64_t ans = 0;
  BIT bit(n + 1);
  for (int i = 0; i < n; ++i) {
    if (i >= k) {
      bit.modify(x[i - k], -1);
      ans -= bit.query(x[i - k] - 1);
    }
    bit.modify(x[i], 1);
    ans += min(i + 1, k) - bit.query(x[i]);
    if (i >= k - 1) cout << ans << " \n"[i == n - 1];
  }

  return 0;
}
