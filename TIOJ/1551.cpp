#include <bits/stdc++.h>
using namespace std;

int64_t modpow(int64_t a, int64_t e, const int64_t mod) {
  int64_t r = 1;
  for (; e; a = a * a % mod, e /= 2)
    if (e & 1) r = r * a % mod;
  return r;
}

int p_in_fac(int p, int n) {
  int cnt = 0;
  while (n >= p) cnt += (n /= p);
  return cnt;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int max_n = 0;
  vector<pair<int, int>> qs;

  for (int n, m; cin >> n >> m; ) {
    qs.emplace_back(n, m);
    max_n = max(max_n, n * 3);
  }

  vector<bool> np(max_n + 1);
  vector<int> prime;
  for (int i = 2; i <= max_n; ++i) {
    if (not np[i]) prime.push_back(i);
    for (int p : prime) {
      if (p * i > max_n) break;
      np[p * i] = true;
      if (p % i == 0) break;
    }
  }

  for (auto [n, m] : qs) {
    // ans = OEIS A001764 = C(3n, n) / (2n+1)
    int64_t ans = 1;
    for (int p : prime) {
      if (p > 3 * n) break;
      int cnt = p_in_fac(p, 3 * n) - p_in_fac(p, 2 * n) - p_in_fac(p, n);
      for (int t = 2 * n + 1; t % p == 0; t /= p) cnt -= 1;
      ans = ans * modpow(p, cnt, m) % m;
    }
    cout << ans << '\n';
  }

  return 0;
}
