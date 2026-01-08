#include <bits/stdc++.h>
using namespace std;

int64_t mow(int64_t x, int e, int mod) {
  int64_t r = 1;
  for (; e; x = x * x % mod, e /= 2)
    if (e & 1) r = r * x % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kC = 1'000'001;
  bitset<kC> np;
  vector<int> primes(1, 2);
  for (int i = 3; i * i < kC; i += 2) if (not np[i])
    for (int j = i * i; j < kC; j += i * 2) np[j] = 1;
  for (int i = 3; i < kC; i += 2)
    if (not np[i]) primes.push_back(i);

  for (int N, M; cin >> N >> M, M; ) {
    int64_t ans = (N < M);
    for (int p : primes) {
      if (ans == 0) break;
      int x = 0;
      for (int t = N; t > 0; ) x += (t /= p);
      ans = ans * mow(p, x, M) % M;
    }
    cout << ans << '\n';
  }

  return 0;
}
