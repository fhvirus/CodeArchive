#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MOD = 1e9 + 7;
void mult(int n, vector<vi>& a, const vector<vi>& b) {
  auto t = a;
  rep (i, 0, n) rep (j, 0, n) t[i][j] = 0;
  rep (i, 0, n) rep (j, 0, n) rep(k, 0, n)
    t[i][j] = int(((ll) a[i][k] * b[k][j] + t[i][j]) % MOD);
  rep (i, 0, n) rep (j, 0, n) a[i][j] = t[i][j];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, k;
  cin >> n >> m >> k;

  vector<vi> x(n, vi(n)), r(n, vi(n));
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    x[a - 1][b - 1] += 1;
  }
  rep (i, 0, n) rep (j, 0, n) r[i][j] = (i == j);
  for (; k; k /= 2, mult(n, x, x))
    if (k & 1) mult(n, r, x);

  cout << r[0][n - 1] << '\n';
}
