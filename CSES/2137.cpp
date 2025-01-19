#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,popcnt")
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

  vector<bitset<3000>> bs(n);
  rep (i, 0, n) {
    string s;
    cin >> s;
    bs[i] = bitset<3000>(s);
  }

  ll ans = 0;
  rep (i, 0, n) rep (j, 0, i) {
    ll cnt = (bs[i] & bs[j]).count();
    ans += cnt * (cnt - 1) / 2;
  }

  cout << ans << '\n';

  return 0;
}
