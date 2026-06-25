#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string A, B;
  int S;
  cin >> A >> B >> S;

  int n = int(size(B));
  if (size(A) < size(B))
    A = string(size(B) - size(A), '0') + A;

  map<tuple<int, int, int>, pair<int64_t, string>> dp;
  const auto solve = [&](const auto& dfs, int i, int j, int k) -> pair<int64_t, string> {
    if (i == n) return j == S ? make_pair(1l, "") : make_pair(0l, "A");
    auto state = make_tuple(i, j, k);
    if (dp.count(state)) return dp.at(state);
    auto [tot, ans] = make_pair(0l, string("A"));
    for (int d = 0; d < 10 and j + d <= S; ++d) {
      int a = int(A[i] - '0'), b = int(B[i] - '0');
      if (((k & 1) == 0 and d < a) or ((k & 2) == 0 and d > b)) continue;
      int n_k = ((k & 1) != 0 or d > a) | (2 * ((k & 2) != 0 or d < b));
      auto [n_tot, n_ans] = dfs(dfs, i + 1, j + d, n_k);
      if (n_tot > 0)
        tot += n_tot, ans = min(ans, string(1, char('0' + d)) + n_ans);
    }
    return dp[state] = make_pair(tot, ans);
  };

  auto [tot, ans] = solve(solve, 0, 0, 0);
  cout << tot << '\n' << ans.substr(ans.find_first_not_of("0")) << '\n';

  return 0;
}

