#include <bits/stdc++.h>
using namespace std;

template <class T>
T modpow(T a, T e, const T mod) {
  T r = 1;
  for (; e; a = a * a % mod, e /= 2)
    if (e & 1) r = r * a % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const uint64_t mod = 100000007; // 1e8 + 7 is prime

  int T;
  cin >> T;
  while (T --> 0) {
    uint64_t N, K, A, B;
    cin >> N >> K >> A >> B;

    if (A == 1 and B == 2) {
      auto g = gcd(K, N);
      cout << (K / g) % mod << ' ' << (N / g) % mod << '\n';
      continue;
    }

    // p(0) = 0, p(N) = 1, (p(i) - p(i-1)) * A/B = (p(i+1) - p(i)) * (1 - A/B)
    // C = B-A, r = (A/B) / (1 - A/B) = A / (B-A) = A/C, gcd(A, C) = 1
    // p(K) = { sum_(i in [0, K-1]) r^i } / { sum_(i in [0, N-1]) r^i }
    //      = (1 - r^K) / (1 - r^N) = C^(N-K) * (C^K - A^K) / (C^N - A^N) = X/Y
    // gcd(X, Y) = gcd(C^K - A^K, C^N - A^N)
    //           = gcd(C^K - A^K, -A^N + C^(N-K) A^K)
    //           = gcd(C^K - A^K, A^K (-A^(N-K) + C^(N-K)))
    //           = gcd(C^K - A^K, C^(N-K) - A^(N-K)) = ... = C^gcd(N, K) - A^gcd(N, K)
    const auto f = [&](auto a, auto c, auto k) {
      a = modpow(a % mod, k, mod);
      c = modpow(c % mod, k, mod);
      return c >= a ? c - a : c + mod - a;
    };
    const uint64_t C = B - A;
    const uint64_t g_inv = modpow(f(A, C, gcd(N, K)), mod - 2, mod);
    const uint64_t P = modpow(C % mod, N - K, mod) * f(A, C, K) % mod * g_inv % mod;
    const uint64_t Q = f(A, C, N) * g_inv % mod;
    cout << P << ' ' << Q << '\n';
  }

  return 0;
}
