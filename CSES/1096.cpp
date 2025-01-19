#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef ll Mat[6][6];

void mult(Mat a, Mat b, const ll mod) {
  Mat t;
  rep (i, 0, 6) rep (j, 0, 6) t[i][j] = 0;
  rep (i, 0, 6) rep (j, 0, 6) rep(k, 0, 6)
    t[i][j] += a[i][k] * b[k][j] % mod;
  rep (i, 0, 6) rep (j, 0, 6)
    a[i][j] = t[i][j] % mod;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  ll n;
  cin >> n;

  Mat x, r;
  rep (i, 0, 6) rep (j, 0, 6) x[i][j] = (i == 0 or j + 1 == i);
  rep (i, 0, 6) rep (j, 0, 6) r[i][j] = (i == j);
  for (; n; n /= 2, mult(x, x, MOD))
    if (n & 1) mult(r, x, MOD);

  cout << r[0][0] << '\n';
}
