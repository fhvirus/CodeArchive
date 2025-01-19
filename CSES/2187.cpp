#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll modpow(ll x, ll e, ll mod) {
  ll r = 1;
  for (; e; e /= 2, x = x * x % mod)
    if (e & 1) r = r * x % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n;
  cin >> n;

  if (n & 1)
    return cout << 0 << '\n', 0;

  string s;
  cin >> s;
  int k = sz(s);

  int cntl = 0, cntr = 0;
  rep (i, 0, k) {
    cntl += (s[i] == '(');
    cntr += (s[i] == ')');
    if (cntl < cntr or cntl * 2 > n)
      return cout << 0 << '\n', 0;
  }

  vector<ll> fac(n + 1), caf(n + 1);
  fac[0] = 1;
  rep (i, 1, n + 1) fac[i] = fac[i - 1] * i % MOD;
  caf[n] = modpow(fac[n], MOD - 2, MOD);
  for (int i = n; i > 0; --i) caf[i - 1] = caf[i] * i % MOD;

  auto C = [&](int n, int k) {
    if (0 > k or k > n) return 0ll;
    return fac[n] * caf[k] % MOD * caf[n - k] % MOD;
  };

  cout << (C(n - k, n / 2 - cntl) - C(n - k, n / 2 - cntl - 1) + MOD) % MOD << '\n';
}
