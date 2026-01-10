#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  int64_t x, a, b, c;
  cin >> x >> a >> b >> c;

  int ans = 0;
  vector<int> v(k);
  for (int bl = 0; bl + k <= n; bl += k) {
    for (int i = 0; i < k; ++i, x = (a * x + b) % c) v[i] = int(x);
    for (int i = k - 1; i > 0; --i) v[i - 1] |= v[i];
    ans ^= v[0];
    int64_t t = x;
    for (int i = 1, p = 0; i < k and bl + i + k <= n;
        ++i, t = (a * t + b) % c) {
      p |= int(t);
      ans ^= (p | v[i]);
    }
  }

  cout << ans << '\n';

  return 0;
}
