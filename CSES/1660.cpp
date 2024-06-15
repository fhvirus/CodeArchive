#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, x;
  cin >> n >> x;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int64_t sum = 0;
  int ans = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n and sum + a[j] <= x) sum += a[j++];
    ans += (sum == x);
    if (j == i) ++j;
    else sum -= a[i];
  }

  cout << ans << '\n';

  return 0;
}
