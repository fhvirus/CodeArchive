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

  ll fac = 1, ans = 1;
  rep (i, 1, n + 1) {
    fac = fac * i % MOD;
    if (i == n / 2 or i == n / 2 + 1)
      ans = ans * modpow(fac, MOD - 2, MOD) % MOD;
  }

  cout << ans * fac % MOD << '\n';
}
