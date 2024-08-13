#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<ll>> mat;

mat operator * (const mat& a, const mat& b) {
  mat c(sz(a), vector<ll>(sz(a)));
  rep (i, 0, sz(a)) rep (k, 0, sz(a)) rep (j, 0, sz(a))
    c[i][j] += a[i][k] * b[k][j];
  for (auto &i : c) for (auto &j : i) j %= 10000;
  return c;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi cand;
  rep (i, 0, 6) rep (j, 0, i)
    cand.push_back((1 << i) | (1 << j));

  vi poss;
  for (int i : cand) for (int j : cand) {
    if ((i & (j >> 2)) != 0 or (j & (i >> 2)) != 0) continue;
    poss.push_back((i << 6) | j);
  }

  ll n;
  cin >> n;

  if (n == 1) return cout << sz(cand) << '\n', 0;
  if (n == 2) return cout << sz(poss) << '\n', 0;
  if (n >= 6) cout << setw(4) << setfill('0');

  mat t(sz(poss), vector<ll>(sz(poss)));
  rep(p, 0, sz(poss)) {
    int i = (poss[p] >> 6), j = (poss[p] & 0b111111);
    for (int k : cand) {
      if ((i & (k >> 1)) != 0 or (k & (i >> 1)) != 0) continue;
      if ((j & (k >> 2)) != 0 or (k & (j >> 2)) != 0) continue;
      t[p][(int) (lower_bound(all(poss), (j << 6) | k) - begin(poss))] += 1;
    }
  }

  mat r(sz(poss), vector<ll>(sz(poss)));
  rep (i, 0, sz(poss)) r[i][i] = 1;
  for (n -= 2; n; n >>= 1) {
    if (n & 1) r = r * t;
    t = t * t;
  }

  ll ans = 0;
  rep (i, 0, sz(poss)) ans += accumulate(all(r[i]), 0ll);
  cout << ans % 10000 << '\n';

  return 0;
}
