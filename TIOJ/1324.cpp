#include <bits/stdc++.h>
using namespace std;

const int kN = 1000001;
int phi[kN];
int64_t modpow(int64_t x, int64_t e, int64_t mod) {
  int64_t r = 1;
  for (; e; e /= 2, x = x * x % mod)
    if (e & 1) r = r * x % mod;
  return r;
}
bool over(int64_t x, int64_t e, int64_t lim) {
  if (x == 1) return lim <= 1;
  if (e >= 20) return true;
  int64_t r = 1;
  for (; e; --e, r *= x)
    if (r >= lim) return true;
  return r >= lim;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  iota(phi, phi + kN, 0);
  for (int i = 2; i < kN; ++i) if (phi[i] == i)
    for (int j = i; j < kN; j += i)
      phi[j] -= phi[j] / i;

  for (int m; cin >> m, m != 0; ) {
    vector<int> x(m);
    for (int &i : x) cin >> i;
    int k; cin >> k;

    x.resize(ranges::find(x, 1) - begin(x));
    if (k == 1 or empty(x)) { cout << 1 % k << '\n'; continue; }
    m = (int)size(x);

    int64_t lim = bit_width((unsigned)k), p = 1;
    while (not empty(x) and p < lim) {
      if (over(x.back(), p, lim)) break;
      p = modpow(x.back(), p, lim);
      x.pop_back();
    }
    if (empty(x)) { cout << p % k << '\n'; continue; }
    m = (int)size(x);

    vector<int> mod(1, k);
    for (int i = 1; i < m and mod.back() != 2; ++i)
      mod.push_back(phi[mod.back()]);
    if ((int)size(mod) < m) {
      m = (int)size(mod);
      p = 1;
    }

    for (int i = m - 1; i >= 0; --i)
      p = modpow(x[i], p, mod[i]) + mod[i];
    cout << p % k << '\n';
  }

  return 0;
}
