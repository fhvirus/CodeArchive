#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int64_t ans = 0;
  map<int, int> mp;
  for (int x, lb = -1, i = 0; i < n; ++i) {
    cin >> x;
    if (mp.count(x)) lb = max(lb, mp.at(x));
    ans += i - lb;
    mp[x] = i;
  }

  cout << ans << '\n';

  return 0;
}
