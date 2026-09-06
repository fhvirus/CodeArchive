#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, d, r; cin >> n >> d >> r; ) {
    vector<int> a(n), b(n);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    ranges::sort(a); ranges::sort(b, greater());
    int ans = 0;
    for (int i = 0; i < n; ++i)
      ans += r * max(0, a[i] + b[i] - d);
    cout << ans << '\n';
  }

  return 0;
}
