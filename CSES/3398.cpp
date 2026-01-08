#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> p(n);
  for (int& i : p) cin >> i, i -= 1;

  vector<int> cnt(n + 1);
  for (int i = 0; i < n; ++i) if (p[i] >= 0) {
    int len = 0;
    for (int u = i; p[u] >= 0; u = exchange(p[u], -1)) len += 1;

    for (int i = 2; i * i <= len; ++i) if (len % i == 0) {
      int c = 0;
      while (len % i == 0) len /= i, c += 1;
      cnt[i] = max(cnt[i], c);
    }
    if (len > 1) cnt[len] = max(cnt[len], 1);
  }

  const int mod = 1e9 + 7;
  int64_t ans = 1;
  for (int i = 2; i <= n; ++i)
    for (int j = 0; j < cnt[i]; ++j)
      ans = ans * i % mod;
  cout << ans << '\n';

  return 0;
}
