#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void mult(ll a[2][2], ll b[2][2], const ll mod) {
  ll t[2][2] = {{0, 0}, {0, 0}};
  rep (i, 0, 2) rep (j, 0, 2) rep(k, 0, 2)
    t[i][j] += a[i][k] * b[k][j] % mod;
  rep (i, 0, 2) rep (j, 0, 2)
    a[i][j] = t[i][j] % mod;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  ll n;
  cin >> n;

  ll x[2][2] = {{1, 1}, {1, 0}};
  ll r[2][2] = {{1, 0}, {0, 1}};
  for (; n; n /= 2, mult(x, x, MOD))
    if (n & 1) mult(r, x, MOD);

  cout << r[0][1] << '\n';
}
