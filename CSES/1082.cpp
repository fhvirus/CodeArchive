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

  const int MOD = 1e9 + 7;
  const int INV2 = (MOD + 1) / 2;

  ll n;
  cin >> n;

  ll ans = 0;
  for (ll l = 1, r, x; l <= n; l = r + 1) {
    x = n / l;
    r = n / x;
    ans += ((l + r) % MOD) * ((r - l + 1) % MOD) % MOD * (x % MOD) % MOD;
  }

  cout << ans % MOD * INV2 % MOD << '\n';
}
