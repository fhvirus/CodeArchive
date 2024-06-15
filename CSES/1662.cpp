#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int64_t sum = 0, ans = 0;
  map<int64_t, int> mp;

  mp[0] = 1;
  for (int a, i = 0; i < n; ++i) {
    cin >> a;
    sum = (sum + a) % n;
    if (sum < 0) sum += n;
    mp[sum] += 1;
  }

  for (auto [_, v] : mp)
    ans += (int64_t) v * (v - 1) / 2;

  cout << ans << '\n';

  return 0;
}
