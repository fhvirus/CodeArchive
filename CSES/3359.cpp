#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<string> a(n);
  for (auto& s : a) cin >> s;

  string ans(1, a[0][0]);
  vector<int> cand(1, 0);
  for (int i = 1; i < n * 2 - 1; ++i) {
    vector<int> ncand;
    for (int u : cand) for (int v : {u, u + 1})
      if (max(0, i - (n - 1)) <= v and v <= min(i, n - 1))
        ncand.push_back(v);
    ncand.erase(begin(ranges::unique(ncand)), end(ncand));
    cand.swap(ncand);

    char c = 'Z';
    for (int j : cand) c = min(c, a[j][i - j]);
    ans.push_back(c);

    cand.erase(begin(ranges::remove_if(cand,
            [&](int j) { return a[j][i - j] != c; })), end(cand));
  }

  cout << ans << '\n';

  return 0;
}
