#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int kN = 20;
ll dp[1 << kN][kN];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1'000'000'007;

  int n, m;
  cin >> n >> m;

  vector<vi> adj(n, vi(n));
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    adj[a - 1][b - 1] += 1;
  }

  dp[1][0] = 1;
  rep (i, 1, 1 << n) rep (j, 0, n) if ((i >> j & 1) and dp[i][j]) {
    rep (k, 0, n) if (not (i >> k & 1))
      dp[i | 1 << k][k] = (dp[i | 1 << k][k] + dp[i][j] * adj[j][k]) % MOD;
  }

  cout << dp[(1 << n) - 1][n - 1] << '\n';

  return 0;
}
