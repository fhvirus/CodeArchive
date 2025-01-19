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
  const int INV2 = (MOD + 1) / 2;

  ll n;
  cin >> n;

  ll t = modpow(2, (n / 2) * (n - n / 2) % (MOD - 1), MOD);
  ll ans = 0;
  for (int i = 1; i <= 4; ++i)
    ans += modpow(t, gcd(i, 4), MOD);
  ans = ans * INV2 % MOD * INV2 % MOD;

  cout << ans * (n & 1 ? 2 : 1) % MOD << '\n';
}
