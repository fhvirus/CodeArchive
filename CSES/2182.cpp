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
  for (; e > 0; e >>= 1, x = x * x % mod)
    if (e & 1) r = r * x % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;
  const int MOD2 = 1e9 + 6;

  int n;
  cin >> n;
  
  vector<ll> x(n), k(n);
  rep (i, 0, n) cin >> x[i] >> k[i];

  { // num
    ll num = 1;
    rep (i, 0, n)
      num = num * (k[i] + 1) % MOD;
    cout << num << ' ';
  }

  { // sum
    ll sum = 1;
    rep (i, 0, n)
      sum = sum * (modpow(x[i], k[i] + 1, MOD) + MOD - 1) % MOD * (modpow(x[i] - 1, MOD - 2, MOD)) % MOD;
    cout << sum << ' ';
  }

  { // prod
    vector<ll> cnt(n, 1);
    for (ll p = 1, i = 0; i < n; ++i) {
      cnt[i] = p;
      p = p * (k[i] + 1) % MOD2;
    }
    for (ll p = 1, i = n - 1; i >= 0; --i) {
      cnt[i] = cnt[i] * p % MOD2;
      p = p * (k[i] + 1) % MOD2;
    }
    ll prod = 1;
    rep (i, 0, n)
      prod = prod * modpow(x[i], cnt[i] * (((k[i] + 1) * k[i] / 2) % MOD2) % MOD2, MOD) % MOD;
    cout << prod << '\n';
  }
}
