#include <bits/stdc++.h>
using namespace std;

struct BIT {
  vector<int> val;
  BIT (int n) : val(n) {}
  void modify(int p, int v) {
    for (; p < int(size(val)); p += p & -p)
      val[p] += v;
  }
  int first_zero() {
    int p = 0, sum = 0;
    for (int l = (1 << __lg(size(val))); l > 0; l /= 2)
      if (p + l < int(size(val)) and sum + val[p + l] == p + l)
        sum += val[p += l];
    return p + 1;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  vector<int> cnt(k);
  BIT bit(k + 1);

  for (int i = 0; i < n; ++i) {
    if (i >= k and x[i - k] < k) {
      if ((cnt[x[i - k]] -= 1) == 0)
        bit.modify(x[i - k] + 1, -1);
    }
    if (x[i] < k) {
      if ((cnt[x[i]] += 1) == 1)
        bit.modify(x[i] + 1, 1);
    }
    if (i >= k - 1) cout << bit.first_zero() - 1 << " \n"[i == n - 1];
  }

  return 0;
}
