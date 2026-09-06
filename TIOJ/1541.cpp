#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;

using big_int = boost::multiprecision::cpp_int;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kC = 1000, kP = 168;
  vector<int> primes;
  for (int i = 2; i < kC; ++i) {
    bool f = true;
    for (int p : primes) {
      if (p * p > i) break;
      if (i % p == 0) { f = false; break; }
    }
    if (f) primes.push_back(i);
  }
  if (kP != (int)size(primes)) exit(-1);

  typedef bitset<kP> bs;

  int n;
  cin >> n;

  array<bs, kP> basis; bs has;

  big_int ans = 1;
  for (int i = 0; i < n; ++i) {
    big_int a; cin >> a;
    bs b;
    for (int j = 0; j < kP; ++j) {
      const int p = primes[j];
      while (a > 1) {
        big_int t = a / p;
        if (t * p != a) break;
        a = t, b.flip(j);
      }
    }
    bool is = false;
    for (auto j = b._Find_first(); j < kP; j = b._Find_next(j)) {
      if (not has[j]) { has[j] = is = true; basis[j] = b; break; }
      b ^= basis[j];
    }
    if (not is) ans *= 2;
  }

  cout << ans - 1 << '\n';

  return 0;
}
