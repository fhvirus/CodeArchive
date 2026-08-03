#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, r;
  cin >> n >> r;

  vector<int> cnt(r, 1), ans;
  for (int i = r - 2; i >= 0; --i) cnt[i] = cnt[i + 1] * (n - i - 1);
  int k = min(n + r, cnt[0] * n);
  for (int i = 0; i < r and cnt[i] > k; ++i) ans.push_back(--n);

  const auto go = [&](const auto& self) -> bool {
    if ((int)size(ans) == r) return (--k) == 0;
    for (int i = n - 1; i >= 0; --i) {
      if (ranges::find(ans, i) != end(ans)) continue;
      ans.push_back(i);
      if (self(self)) return true;
      ans.pop_back();
    }
    return false;
  };

  if (not go(go)) exit(-1);

  for (int i : ans) cout << i;
  cout << endl;

  return 0;
}
