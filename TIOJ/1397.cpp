#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, k; cin >> n >> k; ) {
    int m = n - k;
    string s;
    cin >> s;

    int b = 0;
    for (int i = 1; i <= k; ++i)
      if (s[i] != '0' and s[i] < s[b])
        b = i;
    k = (n - b) - m;

    string ans(1, s[b]);
    ans.reserve(n - b);
    for (int i = b + 1; i < n; ++i) {
      while (k > 0 and (int)size(ans) > 1 and s[i] < ans.back())
        ans.pop_back(), k -= 1;
      ans.push_back(s[i]);
    }
    ans.resize(m);
    cout << ans << '\n';
  }

  return 0;
}
