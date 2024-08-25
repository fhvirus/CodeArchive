#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int kN = 18;
int dp[1 << kN][kN];

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

  if (n == 2)
    return cout << adj[0][1] << '\n', 0;

  rep (i, 1, n - 1)
    dp[1 << (i - 1)][i - 1] = adj[0][i];

  rep (i, 1, 1 << (n - 2)) rep (j, 1, n - 1)
    if ((i >> (j - 1) & 1) and dp[i][j - 1]) {
    rep (k, 1, n - 1) if (not (i >> (k - 1) & 1))
      dp[i | 1 << (k - 1)][k - 1] = (int) ((dp[i | 1 << (k - 1)][k - 1] +
            (ll) dp[i][j - 1] * adj[j][k]) % MOD);
  }

  int ans = 0;
  rep (i, 1, n - 1)
    ans = (int) ((ans +
          (ll) dp[(1 << (n - 2)) - 1][i - 1] * adj[i][n - 1]) % MOD);

  cout << ans << '\n';

  return 0;
}
