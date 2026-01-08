#include <bits/stdc++.h>
using namespace std;

int64_t permToInt(int n, const vector<int>& v) {
  vector<int64_t> fac(n, 1);
  for (int i = 1; i < n; ++i) fac[i] = fac[i - 1] * i;
  int64_t r = 1, a = ((1 << (n + 1)) - 2);
  for (int i = 0; i < n; ++i) {
    r += fac[n - i - 1] * __builtin_popcount(a & ((1 << v[i]) - 1));
    a ^= (1 << v[i]);
  }
  return r;
}
vector<int> intToPerm(int n, int64_t k) {
  vector<int64_t> fac(n, 1);
  for (int i = 1; i < n; ++i) fac[i] = fac[i - 1] * i;
  vector<int> v, a(n + 1); iota(begin(a), end(a), 0);
  for (int i = n; i > 0; --i) {
    int64_t t = (k + fac[i - 1] - 1) / fac[i - 1];
    k -= (t - 1) * fac[i - 1];
    v.push_back(a[t]);
    a.erase(begin(a) + t);
  }
  return v;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;

  while (t --> 0) {
    int type;
    cin >> type;
    if (type == 1) {
      int n;
      int64_t k;
      cin >> n >> k;
      auto v = intToPerm(n, k);
      for (int i : v) cout << i << " \n"[i == v.back()];
    } else {
      int n;
      cin >> n;
      vector<int> v(n);
      for (int &i : v) cin >> i;
      cout << permToInt(n, v) << '\n';
    }
  }

  return 0;
}
