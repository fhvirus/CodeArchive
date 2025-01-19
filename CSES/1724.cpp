#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef vector<ll> vl;
void mult(int n, vector<vl>& a, const vector<vl>& b) {
  auto t = a;
  rep (i, 0, n) rep (j, 0, n) t[i][j] = LLONG_MAX / 2;
  rep (i, 0, n) rep (j, 0, n) rep(k, 0, n)
    t[i][j] = min(t[i][j], a[i][k] + b[k][j]);
  rep (i, 0, n) rep (j, 0, n) a[i][j] = t[i][j];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, k;
  cin >> n >> m >> k;

  vector<vl> x(n, vl(n, LLONG_MAX / 2)), r(n, vl(n, LLONG_MAX / 2));
  for (int a, b, c, i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    x[a - 1][b - 1] = min<ll>(x[a - 1][b - 1], c);
  }
  r[0][0] = 0;
  for (; k; k /= 2, mult(n, x, x))
    if (k & 1) mult(n, r, x);

  cout << r[0][n - 1] << '\n';
}
