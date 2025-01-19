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

  string s;
  cin >> s;
  int n = sz(s);

  vector<ll> fac(n + 1), caf(n + 1);
  fac[0] = 1;
  rep (i, 1, n + 1) fac[i] = fac[i - 1] * i % MOD;
  caf[n] = modpow(fac[n], MOD - 2, MOD);
  for (int i = n; i >= 1; --i) caf[i - 1] = caf[i] * i % MOD;

  vi cnt(26);
  for (char c : s) cnt[c - 'a'] += 1;

  ll ans = 1;
  rep (i, 0, 26) {
    ans = ans * fac[n] % MOD * caf[cnt[i]] % MOD * caf[n - cnt[i]] % MOD;
    n -= cnt[i];
  }
  cout << ans << '\n';
}
