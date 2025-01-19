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
  const int kN = 1e6 + 1;

  vector<ll> fac(kN), caf(kN);
  fac[0] = 1;
  rep (i, 1, kN) fac[i] = fac[i - 1] * i % MOD;
  caf[kN - 1] = modpow(fac[kN - 1], MOD - 2, MOD);
  for (int i = kN - 1; i >= 1; --i) caf[i - 1] = caf[i] * i % MOD;

  int n;
  cin >> n;

  for (int a, b, i = 0; i < n; ++i) {
    cin >> a >> b;
    cout << fac[a] * caf[b] % MOD * caf[a - b] % MOD << '\n';
  }
}
