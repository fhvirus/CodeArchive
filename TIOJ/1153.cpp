#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> s(n), t(n);
  for (int &i : s) cin >> i;

  int tid, num, ans_t = 0, ans_i = 0;
  while (cin >> tid >> num, tid or num) {
    int best_i = 0, best_t = INT_MAX;
    for (int i = 0; i < n; ++i) {
      // Not correct according to the description, should be counting seconds.
      int cur_t = max(t[i], tid) + (num + s[i] - 1) / s[i] + 15;
      if (make_pair(cur_t, -s[i]) < make_pair(best_t, -s[best_i]))
        best_i = i, best_t = cur_t;
    }
    if (ans_t < max(t[best_i], tid) + 5)
      ans_t = max(t[best_i], tid) + 5, ans_i = best_i;
    t[best_i] = best_t;
  }

  cout << ans_t << ' ' << ans_i + 1 << '\n';

  return 0;
}
