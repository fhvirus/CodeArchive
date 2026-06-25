#include <bits/stdc++.h>
using namespace std;


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // LDRU
  const pair<int, int> INF(INT_MAX / 2, -1);
  const auto pack = [](int l, int r, int last) { return l + r * 0b100 + last * 0b10000; };
  const auto cost = [](int s, int t, int last) {
    return last == 0 ? (s == t ? 3 : 5 + 2 * (abs(s - t) == 2)) : 1; };

  for (string s; cin >> s, s[0] != '#'; ) {
    int n = int(size(s));

    vector<array<pair<int, int>, 4 * 4 * 3>> dp(n + 1);
    for (int i = 0; i <= n; ++i) ranges::fill(dp[i], INF);
    dp[0][pack(0, 2, 2)] = make_pair(0, -1);

    for (int i = 0; i < n; ++i) {
      for (int l : {0, 1, 2, 3}) for (int r : {0, 1, 2, 3}) for (int k : {0, 1, 2}) {
        int state = pack(l, r, k);
        auto& src = dp[i][state];
        for (int t : {0, 1, 2, 3}) {
          if (l == t or (r != 0 and r != t)) {
            auto& des = dp[i + 1][pack(t, r, 0)];
            des = min(des, make_pair(src.first + cost(l, t, k), state));
          }
          if (r == t or (l != 2 and l != t)) {
            auto& des = dp[i + 1][pack(l, t, 1)];
            des = min(des, make_pair(src.first + cost(r, t, k ^ 1), state));
          }
        }
        if (s[i] == '.') {
          auto& des = dp[i + 1][pack(l, r, 2)];
          des = min(des, make_pair(src.first, state));
        }
      }
      for (int l : {0, 1, 2, 3}) for (int r : {0, 1, 2, 3}) for (int k : {0, 1, 2})
        if (s[i] != '.' and (k == 2 or (k == 0 ? l : r) != int("LDRU"s.find(s[i]))))
          dp[i+1][pack(l, r, k)] = INF;
    }

    string ans;
    for (int i = n, j = int(ranges::min_element(dp[n]) - begin(dp[n])); i > 0; --i) {
      ans.push_back("LR."[j >> 4]);
      j = dp[i][j].second;
    }
    ranges::reverse(ans);
    cout << ans << '\n';
  }

  return 0;
}
