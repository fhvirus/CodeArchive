#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  const auto get_t = [&a](int t, int i) { return (t + a[i] - 1) / a[i] * a[i]; };
  const auto get_id = [&n](int i, int j) { return ((i >> (n - 1) & 1) ? i ^ ((1 << n) - 1): i) * n + j; };

  vector<int> dp((1 << (n - 1)) * n, INT_MAX);
  for (int i = 1; i < (1 << n); ++i) {
    if ((i & (i - 1)) == 0) {
      int j = __lg(i);
      dp[get_id(i, j)] = get_t(1 + j, j);
      continue;
    }
    for (int u = i, j = __lg(u & -u); u; u ^= 1 << j, j = __lg(u & -u))
      for (int p = (i ^ (1 << j)), k = __lg(p & -p); p; p ^= 1 << k, k = __lg(p & -p))
        dp[get_id(i, j)] = min(dp[get_id(i, j)],
            get_t(dp[get_id((i ^ (1 << j)), k)] + abs(j - k), j));
  }

  cout << *min_element(begin(dp), begin(dp) + n) << '\n';

  return 0;
}
