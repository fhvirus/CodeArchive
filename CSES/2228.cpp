#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const ll mod = 1e9 + 7;

  int n, k;
  cin >> n >> k;

  const auto modpow = [&](ll x, ll e) -> ll {
    ll r = 1;
    for (; e; x = x * x % mod, e /= 2)
      if (e & 1) r = r * x % mod;
    return r;
  };

  ll choose = 1, ans = 0;
  rep (i, 0, k) {
    ll cur = modpow(k - i, n) * choose % mod;
    if (i % 2 == 0) ans = (ans + cur) % mod;
    else ans = (ans - cur + mod) % mod;
    choose = choose * (k - i) % mod * modpow(i + 1, mod - 2) % mod;
  }

  cout << ans << '\n';

  return 0;
}
