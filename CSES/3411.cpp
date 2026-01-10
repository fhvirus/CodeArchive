#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector a(2, vector<int>(n));
  for (int i = 0; i < n; ++i)
    cin >> a[0][i] >> a[1][i];

  __int128 ans = 0;
  for (auto &v : a) {
    ranges::sort(v);
    for (int i = 1; i < n; ++i)
      ans += __int128(v[i] - v[i - 1]) * i * (n - i);
  }

  const int64_t kK = 1e9;
  if (ans >= kK) {
    cout << int64_t(ans / kK);
    cout << setw(9) << setfill('0') << int64_t(ans % kK) << '\n';
  } else cout << int64_t(ans) << '\n';

  return 0;
}
