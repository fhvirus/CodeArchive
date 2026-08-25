#include <bits/stdc++.h>
using namespace std;

int euclid(int a, int b, int &x, int &y) {
  if (b == 0) return x = 1, y = 0, a;
  int d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}
int crt(int a, int m, int b, int n) {
  if (n > m) swap(a, b), swap(m, n);
  int x, y, g = euclid(m, n, x, y);
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m*n/g : x;
}
int modpow(int x, int e, const int mod) {
  int r = 1;
  for (; e; e /= 2, x = x * x % mod)
    if (e & 1) r = r * x % mod;
  return r;
}

// 32512: 2^8 * 127
// 32513: 13  * 41 * 61
// 32612: 2^2 * 31 * 263
const int mod[3] = {32512, 32513, 32612};
const int ps[6] = {127, 13, 41, 61, 31, 263};

int solve_p(int m, int n, const int p) {
  vector<int> fac(p), caf(p);
  fac[0] = 1;
  for (int i = 1; i < p; ++i) fac[i] = fac[i - 1] * i % p;
  caf[p - 1] = modpow(fac[p - 1], p - 2, p);
  for (int i = p - 1; i > 0; --i) caf[i - 1] = caf[i] * i % p;
  const auto C = [&](int a, int b) {
    if (0 > b or b > a or a >= p) return 0;
    return fac[a] * caf[b] % p * caf[a - b] % p;
  };

  vector<int> dm, dn;
  for (int t = n; t > 0; t /= p) dn.push_back(t % p);
  for (int t = m; t > 0; t /= p) dm.push_back(t % p);
  ranges::reverse(dn);
  dm.resize(size(dn)); ranges::reverse(dm);

  array<int, 2> sc {0, 1}, dp;
  for (int i = 0; i < (int)size(dn); ++i) {
    int sum = 0;
    dp[0] = 0;
    for (int j = 0; j < p; ++j) {
      sum = (sum + C(dm[i], j)) % p;
      if (j == dn[i] - 1) dp[0] += sc[1] * sum % p;
    }
    dp[0] = (dp[0] + sc[0] * sum) % p;
    dp[1] = sc[1] * C(dm[i], dn[i]) % p;
    swap(sc, dp);
  }

  return (sc[0] + sc[1]) % p;
}

int solve_256(int m, int n) {
  vector<int> inv(256, 1);
  for (int i = 1; i < 256; i += 2)
    inv[i] = modpow(i, 127, 256);

  bool f = (n + 1 > m - n);
  if (f) n = m - n - 1;

  int sum = (n >= 0 ? 1 : 0), val = 1, cnt2 = 0;
  for (int i = 1; i <= n; ++i) {
    auto la = countr_zero((unsigned)(m + 1 - i));
    auto lb = countr_zero((unsigned)i);
    cnt2 += la - lb;
    val = val * (((m + 1 - i) >> la) % 256) * inv[(i >> lb) % 256] % 256;
    sum += (val << min(8, cnt2)) % 256;
  }
  sum %= 256;

  return f ? (modpow(2, m, 256) + 256 - sum) % 256 : sum;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m, n;
  cin >> m >> n;
  n = min(m, n);

  array<int, 6> sum;
  for (int i = 0; i < 6; ++i)
    sum[i] = (solve_p(m, n, ps[i]) + ps[i] - 1) % ps[i];

  int sum_256 = (solve_256(m, n) + 255) % 256;

  array<int, 3> ans;
  ans[0] = crt(sum_256, 256, sum[0], ps[0]);
  ans[1] = crt(sum[1], ps[1], sum[2], ps[2]);
  ans[1] = crt(ans[1], ps[1] * ps[2], sum[3], ps[3]);
  ans[2] = crt(sum[4], ps[4], sum[5], ps[5]);
  ans[2] = crt(ans[2], ps[4] * ps[5], sum_256 % 4, 4);

  for (int i : {0, 1, 2})
    cout << ans[i] << " \n"[i == 2];

  return 0;
}
