#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, x;
  cin >> n >> x;

  vector<int> h(n), s(n);
  for (int &i : h) cin >> i;
  for (int &i : s) cin >> i;

  vector<int> dp(x + 1);
  for (int i = 0, sum = 0; i < n; ++i) {
    for (int j = min(sum, x - h[i]); j >= 0; --j)
      dp[j + h[i]] = max(dp[j + h[i]], dp[j] + s[i]);
    sum = min(sum + h[i], x);
  }

  cout << *max_element(begin(dp), end(dp)) << '\n';

  return 0;
}
