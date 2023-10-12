#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kN = 200002;
  const int kS = 46341; // ceil(sqrt(INT_MAX))
  bitset<kN> not_prime;

  int T;
  cin >> T;
  while (T --> 0) {
    uint32_t L, R;
    cin >> L >> R;

    not_prime.reset();
    for (uint32_t i = 2; i < kS and i * i <= R; ++i) {
      for (uint32_t j = max(((L + i - 1) / i) * i, 2 * i); j <= R; j += i)
        not_prime[j - L] = 1;
    }

    cout << (R - L + 1) - not_prime.count() << '\n';
  }

  return 0;
}
