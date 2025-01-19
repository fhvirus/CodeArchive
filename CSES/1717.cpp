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

  const int MOD = 1e9 + 7;

  int n;
  cin >> n;

  vector<ll> dp(4);
  dp[1] = 0, dp[2] = 1;

  rep (i, 3, n + 1)
    dp[i & 3] = (i - 1) * (dp[(i - 1) & 3] + dp[(i - 2) & 3]) % MOD;

  cout << dp[n & 3] << '\n';
}
