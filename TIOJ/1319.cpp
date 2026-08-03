#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n + 3);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i : {0, 1, 2}) a[n + i] = a[i];

  int64_t ori = (int64_t) a[0] * a[n - 1];
  for (int i = 1; i < n; ++i)
    ori += (int64_t) a[i - 1] * a[i];

  int64_t ans = 0;
  for (int i = 1; i <= n; ++i) {
    int64_t t = a[i - 1] + a[i + 1] - a[i] - a[i + 2] + k;
    int64_t x = clamp<int64_t>(t / 2, 0, k);
    ans = max(ans, (int64_t) k * (a[i] + a[i + 2]) + t * x - x * x);
  }

  cout << setprecision(4) << fixed << (long double) (ans + ori) / ori << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;
  while (t --> 0) solve();

  return 0;
}
