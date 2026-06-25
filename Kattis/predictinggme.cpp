#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> dp(3), sc(3, INT_MIN / 2);
  sc[0] = 0;
  for (int p, i = 0; i < N; ++i) {
    cin >> p;
    dp[0] = max(sc[0], sc[2]);
    dp[1] = max(sc[1], sc[0] - p);
    dp[2] = sc[1] + p;
    swap(dp, sc);
  }

  cout << max(sc[0], sc[2]) << '\n';

  return 0;
}
