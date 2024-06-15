#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<pair<int, int>> movies(n);
  for (auto &[b, a] : movies)
    cin >> a >> b;

  sort(begin(movies), end(movies));

  multiset<int> members;
  for (int i = 0; i < k; ++i)
    members.insert(0);

  int ans = 0;
  for (auto [b, a] : movies) {
    if (a < *begin(members)) continue;
    auto it = prev(members.upper_bound(a));
    members.erase(it);
    members.insert(b);
    ans += 1;
  }

  cout << ans << '\n';

  return 0;
}
