#include <bits/stdc++.h>
using namespace std;

template <int64_t mod>
struct SquareMatrix {
  typedef SquareMatrix M;
  int n;
  vector<int64_t> a;
  SquareMatrix(int _n) : n(_n), a(n * n) {}
  int64_t& operator () (int i, int j) { return a[i * n + j]; }
  M operator * (const M& o) const {
    M r(n);
    for (int i = 0; i < n; ++i) for (int k = 0; k < n; ++k) {
      for (int j = 0; j < n; ++j)
        r.a[i * n + k] += a[i * n + j] * o.a[j * n + k] % mod;
      r.a[i * n + k] %= mod;
    }
    return r;
  }
};

int64_t modpow(int64_t a, int64_t e, const int64_t mod) {
  int64_t r = 1;
  for (; e; a = a * a % mod, e /= 2)
    if (e & 1) r = r * a % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int64_t mod = 1e9 + 7;

  int N, K, G;
  cin >> N >> K >> G;

  if (N == K) K -= 1;

  vector<int64_t> f(G + 2, 0);
  if ((int64_t) G * K <= (int64_t) G * G * 30) {
    vector<int64_t> dp(G + 2);
    f[1] = 1;
    for (int i = 2; i <= K; ++i) {
      dp[0] = dp[G + 1] = 0;
      for (int j = 1; j <= G; ++j)
        dp[j] = (f[j - 1] * (j - 1) + f[j] * 2 * j + f[j + 1] * (j + 1)) % mod;
      swap(dp, f);
    }
  } else {
    SquareMatrix<mod> T(G + 1), res(G + 1);
    for (int i = 1; i <= G; ++i) {
      if (i > 1) T(i, i - 1) = i - 1;
      T(i, i) = 2 * i;
      if (i < G) T(i, i + 1) = i + 1;
    }
    for (int i = 1; i <= G; ++i) res(i, i) = 1;
    for (int e = K - 1; e > 0; T = T * T, e /= 2)
      if (e & 1) res = res * T;
    for (int i = 1; i <= G; ++i) f[i] = res(i, 1);
  }

  int64_t ans = 0, num = 1; // num = C((N-K-i) + (i-1), i-1) = C(N-K-1, i-1)
  for (int i = 1; i <= G; ++i) {
    ans += f[i] * num % mod;
    num = num * (N - K - i) % mod * modpow(i, mod - 2, mod) % mod;
  }

  cout << (ans % mod * N) % mod << '\n';

  return 0;
}
