#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<int> h(n);
  for (int &i : h) cin >> i;

  vector<vector<pair<int, int>>> qs(n);
  for (int a, b, i = 0; i < q; ++i) {
    cin >> a >> b;
    qs[a - 1].emplace_back(b - 1, i);
  }

  vector<int> stk, ans(q);
  for (int i = n - 1; i >= 0; --i) {
    while (not stk.empty() and h[stk.back()] <= h[i])
      stk.pop_back();
    stk.push_back(i);

    for (auto [b, id] : qs[i])
      ans[id] = int(end(stk) - ranges::lower_bound(stk, b, greater<int>()));
  }

  for (int i : ans) cout << i << '\n';
  
  return 0;
}
