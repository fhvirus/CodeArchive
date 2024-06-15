#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  vector<int64_t> pre(n + 1);
  for (int i = 1; i <= n; ++i)
    pre[i] = pre[i - 1] + x[i - 1];

  vector<int64_t> dp(n), sc(n);
  for (int i = 0; i < n; ++i) sc[i] = x[i];
  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j + i <= n; ++j)
      dp[j] = pre[j + i] - pre[j] - min(sc[j], sc[j + 1]);
    swap(dp, sc);
  }

  cout << sc[0] << '\n';

  return 0;
}
