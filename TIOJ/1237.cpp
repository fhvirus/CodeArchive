#include <bits/stdc++.h>
using namespace std;

const int kN = 2'000'000;
int a[kN], mx[kN];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  const int k = (n - 1) / 2;
  int len = INT_MAX;

  for (int i = 0; i < k; ++i)
    mx[k - 1 - i] = max(a[n - 1 - i], mx[k - i]);
  for (int b = 0; b < n; b += k) {
    for (int i = 0, cmx = 0; i < k and b + i < n; ++i) {
      cmx = max(cmx, a[b + i]);
      len = min(len, max(cmx, mx[i + 1]));
    }
    if (b + k >= n) break;
    for (int i = 0; i < k; ++i)
      mx[k - 1 - i] = max(a[b + k - 1 - i], mx[k - i]);
  }

  int64_t ans = 0;
  for (int i = 0; i < n; ++i)
    if (a[i] >= len) ans += a[i] - len;
  cout << ans << endl;

  return 0;
}
