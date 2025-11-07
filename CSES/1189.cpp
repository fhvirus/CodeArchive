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

  int n;
  cin >> n;

  vector<ll> a(n), b(n);
  for (ll &i : a) cin >> i;
  for (ll &i : b) cin >> i;
  rep (i, 0, n) a[i] = a[i] - b[i] + (i > 0 ? a[i - 1] : 0);

  ll ans = a.back();
  a.back() = 0;
  int t = (n - 1) / 2;
  nth_element(begin(a), begin(a) + t, end(a));
  for (ll i : a) ans += abs(i - a[t]);

  cout << ans << '\n';

  return 0;
}
