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

  int n, m;
  cin >> n >> m;

  vector<ll> ans(n + 1);
  ll tot = 0;
  rep (i, 1, n + 1) {
    ans[i] = (ans[i] + modpow(m, i, MOD)) * modpow(i, MOD - 2, MOD) % MOD;
    if (n % i == 0) tot += ans[i];
    for (int j = i + i; j <= n; j += i)
      ans[j] = (ans[j] - ans[i] * i % MOD + MOD) % MOD;
  }

  cout << tot % MOD << '\n';
}
