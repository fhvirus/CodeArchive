#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll modpow(ll x, ll e, const ll mod) {
  ll r = 1;
  for (; e; e /= 2, x = x * x % mod)
    if (e & 1) r = r * x % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n, m;
  cin >> n >> m;
  int t = n + m - 1;

  vector<ll> fac(t + 1), caf(t + 1);
  fac[0] = 1;
  rep (i, 1, t + 1) fac[i] = fac[i - 1] * i % MOD;
  caf[t] = modpow(fac[t], MOD - 2, MOD);
  for (int i = t; i >= 1; --i) caf[i - 1] = caf[i] * i % MOD;

  cout << fac[n + m - 1] * caf[n - 1] % MOD * caf[m] % MOD << '\n';
}
