#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  array<int, 3> cnt {};
  int64_t ans = 0;
  for (char c : s) {
    int i = c - '0';
    cnt[i] += 1;
    for (++i; i < 3; ++i)
      ans += cnt[i];
  }

  cout << ans << '\n';

  return 0;
}
