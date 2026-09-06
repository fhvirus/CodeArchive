#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int p, t; cin >> p >> t; ) {
    vector<int> w(p);
    for (int &i : w) cin >> i;

    vector<int> sc(p + 1, INT_MAX), dp(p + 1);
    sc[0] = 0;
    for (int i = 0; i < t; ++i) {
      ranges::fill(dp, INT_MAX);
      for (int j = 0; j < p; ++j) if (sc[j] < INT_MAX)
        for (int sum = 0, k = j; k < p; ++k) {
          sum += w[k];
          dp[k + 1] = min(dp[k + 1], max(sum, sc[j]));
        }
      swap(dp, sc);
    }

    cout << sc[p] << '\n';
  }

  return 0;
}
