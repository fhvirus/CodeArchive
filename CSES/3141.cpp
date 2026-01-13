#include <bits/stdc++.h>
using namespace std;

const int64_t mod = 1e9 + 7;
int64_t modpow(int64_t x, int64_t e) {
  int64_t r = 1;
  for (; e; x = x * x % mod, e /= 2)
    if (e & 1) r = r * x % mod;
  return r;
}
void SOS(int m, auto &a, auto op) {
  for (int l = 1; l < m; l *= 2)
    for (int i = 0; i < m; i += 2 * l)
      for (int j = i; j < i + l; ++j)
        a[j] = op(a[j], a[j + l]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int m = 2 << __lg(n);
  vector<int64_t> a(m);
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    a[x] += 1;
  }

  SOS(m, a, plus());
  for (int i = 0; i < m; ++i)
    a[i] = modpow(2, a[i]) - 1;
  SOS(m, a, minus());

  for (int i = 0; i <= n; ++i)
    cout << (a[i] % mod + mod) % mod << " \n"[i == n];

  return 0;
}
