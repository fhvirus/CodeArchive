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

  ll n;
  int k;
  cin >> n >> k;

  vector<ll> a(k);
  for (ll &i : a) cin >> i;

  ll ans = 0;
  rep (i, 1, (1 << k)) {
    __int128 prod = -1;
    rep (j, 0, k) if (i >> j & 1) {
      prod *= -a[j];
      if (prod > n) break;
    }
    ans += ll(n / prod);
  }

  cout << ans << '\n';
}
