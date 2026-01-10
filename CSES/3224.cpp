#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  int cnt_mode = 0;
  map<int, int> cnt;
  vector<set<int>> cand(k + 1);
  for (int &i : x) cand[0].insert(i);
  for (int i = 0; i < n; ++i) {
    if (i >= k) {
      auto &u = cnt[x[i - k]];
      cand[u].erase(cand[u].find(x[i - k]));
      u -= 1;
      cand[u].insert(x[i - k]);
      if (empty(cand[cnt_mode])) cnt_mode -= 1;
    }
    {
      auto &u = cnt[x[i]];
      cand[u].erase(cand[u].find(x[i]));
      u += 1;
      cand[u].insert(x[i]);
      cnt_mode = max(cnt_mode, u);
    }
    if (i >= k - 1) cout << *begin(cand[cnt_mode]) << " \n"[i == n - 1];
  }

  return 0;
}
