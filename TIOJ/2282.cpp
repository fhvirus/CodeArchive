#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int k, n;
  cin >> k >> n;

  vector<vector<pii>> adj(k);
  for (int a, b, w, i = 0; i < n; ++i) {
    cin >> a >> b >> w;
    if (a < b) swap(a, b);
    adj[a - 1].emplace_back(b - 1, w);
  }

  vi dp(1 << k), sc(1 << k);
  sc[0] = 1;
  for (int u = k - 1; u > 0; --u) {
    for (auto [v, w] : adj[u]) {
      for (int i = 0; i < (1 << (u + 1)); ++i) {
        dp[i] = sc[i];
        if (sc[i ^ (1 << u) ^ (1 << v)])
          dp[i] = (int) ((ll) w * sc[i ^ (1 << u) ^ (1 << v)] % MOD + dp[i]) % MOD;
      }
      swap(dp, sc);
    }
  }
  cout << (sc[0] == 0 ? MOD - 1 : sc[0] - 1) << '\n';

  return 0;
}
