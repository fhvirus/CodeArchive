#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int64_t modpow(int64_t x, int64_t e) {
  int64_t r = 1;
  for (; e; x = x * x % mod, e /= 2)
    if (e & 1) r = r * x % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector a(n, valarray<int64_t>(m + 1));
  for (auto &i : a) for (auto &j : i) cin >> j;

  int rank = 0;
  vector<int> col(n);
  for (int c = 0; c < m and rank < n; ++c) {
    for (int r = rank; r < n; ++r) if (a[r][c]) {
      a[r].swap(a[rank]);
      break;
    }
    if (a[rank][c] == 0) continue;
    col[rank] = c;

    a[rank] = a[rank] * modpow(a[rank][c], mod - 2) % mod;
    for (int r = rank + 1; r < n; ++r)
      a[r] = (a[r] - a[rank] * a[r][c] % mod + mod) % mod;
    rank += 1;
  }

  for (int r = rank; r < n; ++r) if (a[r][m]) {
    cout << "-1\n";
    exit(0);
  }

  vector<int> x(m);
  for (int r = rank - 1; r >= 0; --r) {
    int64_t v = a[r][m];
    for (int c = col[r] + 1; c < m; ++c)
      v -= a[r][c] * x[c] % mod;
    v = (v % mod + mod) % mod;
    x[col[r]] = int(v);
  }

  for (int c = 0; c < m; ++c)
    cout << x[c] << " \n"[c == m - 1];

  return 0;
}
