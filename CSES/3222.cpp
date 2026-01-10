#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  int ans = 0;
  map<int, int> mp;
  for (int i = 0; i < n; ++i) {
    if (i >= k and (mp[x[i - k]] -= 1) == 0) --ans;
    if ((mp[x[i]] += 1) == 1) ++ans;
    if (i >= k - 1) cout << ans << " \n"[i == n - 1];
  }

  return 0;
}
