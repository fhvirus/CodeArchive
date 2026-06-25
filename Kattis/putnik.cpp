#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int INF = INT_MAX - 1000;

  int N;
  cin >> N;

  vector a(N, vector<int>(N));
  for (auto &i : a) for (auto &j : i) cin >> j;

  vector<int> dp(N), sc(N, INF);
  sc[0] = 0;
  for (int i = 1; i < N; ++i) {
    ranges::fill(dp, INF);
    for (int j = 0; j < i; ++j) dp[j] = sc[j] + a[i - 1][i];
    for (int j = 0; j < i; ++j) dp[i - 1] = min(dp[i - 1], sc[j] + a[j][i]);
    dp.swap(sc);
  }

  cout << *ranges::min_element(sc) << '\n';

  return 0;
}

