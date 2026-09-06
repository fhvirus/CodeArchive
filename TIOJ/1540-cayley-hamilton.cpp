#include <bits/stdc++.h>
using namespace std;

int64_t modpow(int64_t a, int64_t e, const int64_t mod) {
  int64_t r = 1;
  for (; e; a = a * a % mod, e /= 2)
    if (e & 1) r = r * a % mod;
  return r;
}

const int64_t mod = 1e9 + 7;

auto tridiagonal_charpoly(int n, const auto& a, const auto& b, const auto& c) {
  vector<int64_t> pa(n + 1, 0), pb(n + 1), pc(n + 1);
  pb[1] = 1, pb[0] = (mod - a[0]) % mod;
  for (int i = 1; i < n; ++i) {
    // p_i = (x - a[i]) * p_(i - 1) - b[i - 1] * c[i] * p_(i - 2)
    for (int j = 0; j <= i + 1; ++j) {
      pc[j] = 0;
      if (j > 0) pc[j] += pb[j - 1];
      pc[j] += (mod - a[i]) * pb[j] % mod;
      pc[j] += mod - b[i - 1] * c[i] % mod * pa[j] % mod;
      pc[j] %= mod;
    }
    swap(pa, pb); swap(pb, pc);
  }
  return pb;
}

auto pow_x_mod(int e, const auto& p) {
  const int n = (int)size(p) - 1;
  const auto mul = [&](const auto& a, const auto& b) {
    vector<int64_t> r(n * 2 - 1);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
      r[i + j] = (r[i + j] + a[i] * b[j]) % mod;
    for (int i = 2 * n - 2; i >= n; --i) for (int j = 0; j < n; ++j)
      r[i - n + j] = (r[i - n + j] - r[i] * p[j] % mod + mod) % mod;
    r.resize(n);
    return r;
  };
  vector<int64_t> r(n), x = r;
  r[0] = x[1] = 1;
  for (; e > 0; x = mul(x, x), e /= 2)
    if (e & 1) r = mul(r, x);
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K, G;
  cin >> N >> K >> G;

  if (N == K) K -= 1;

  vector<int64_t> f(G + 2, 0);
  if ((int64_t) G * K <= (int64_t) G * G * __lg(K + 1)) {
    vector<int64_t> dp(G + 2);
    f[1] = 1;
    for (int i = 2; i <= K; ++i) {
      dp[0] = dp[G + 1] = 0;
      for (int j = 1; j <= G; ++j)
        dp[j] = (f[j - 1] * (j - 1) + f[j] * 2 * j + f[j + 1] * (j + 1)) % mod;
      swap(dp, f);
    }
  } else {
    // char. poly. of tridiagonal matrix T
    vector<int64_t> a(G + 1), b(G + 1), c(G + 1);
    for (int i = 1; i <= G; ++i) {
      if (i > 1) c[i] = i - 1;
      a[i] = 2 * i;
      if (i < G) b[i] = i + 1;
    }
    auto p = tridiagonal_charpoly(G + 1, a, b, c);

    // Cayley-Hamilton thm.:
    // given f(x) = poly of x, f(A) = 0
    // => A^n = -f(A) + A^n
    auto g = pow_x_mod(K - 1, p);
    vector<int64_t> sc(G + 2), dp(G + 2);
    sc[1] = 1;
    for (int i = 0; i < (int)size(p) - 1; ++i) {
      for (int j = 0; j <= G + 1; ++j) f[j] += sc[j] * g[i] % mod;
      dp[0] = dp[G + 1] = 0;
      for (int j = 1; j <= G; ++j)
        dp[j] = (sc[j - 1] * (j - 1) + sc[j] * 2 * j + sc[j + 1] * (j + 1)) % mod;
      swap(dp, sc);
    }
    for (auto &i : f) i %= mod;
  }

  int64_t ans = 0, num = 1; // num = C((N-K-i) + (i-1), i-1) = C(N-K-1, i-1)
  for (int i = 1; i <= G; ++i) {
    ans += f[i] * num % mod;
    num = num * (N - K - i) % mod * modpow(i, mod - 2, mod) % mod;
  }

  cout << (ans % mod * N) % mod << '\n';

  return 0;
}
