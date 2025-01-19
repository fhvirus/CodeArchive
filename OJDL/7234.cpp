#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  typedef long long ll;
  const ll mod = 1e9 + 8;

  int N, K;
  cin >> N >> K;

  vector<ll> dp(N + 1);
  dp[N] = 1;

  for (int i = N - 1; i >= 1; --i) {
    ll mul = 2;
    for (int j = i + 1; j <= N and j <= i + K; ++j) {
      dp[i] = (dp[i] + dp[j] * mul) % mod;
      mul = (mul * (N - j)) % mod;
    }
  }
  cout << dp[1] << '\n';

  return 0;
}
