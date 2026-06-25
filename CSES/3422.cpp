#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  if (n <= 2) {
    cout << "IMPOSSIBLE\n";
    exit(0);
  }

  vector<int> a(n), b(n), ans(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  set<int> left;
  for (int i = 1; i <= n; ++i) left.insert(i);
  for (int i = 0; i + 4 < n; ++i) {
    auto it = begin(left);
    while (*it == a[i] or *it == b[i]) ++it;
    ans[i] = *it;
    left.erase(it);
  }

  int k = int(size(left));
  for (int i = n - k; i < n; ++i) {
    ans[i] = *begin(left);
    left.erase(begin(left));
  }
  do {
    bool can = true;
    for (int i = n - k; i < n; ++i)
      can &= (ans[i] != a[i] and ans[i] != b[i]);
    if (can) break;
  } while (next_permutation(end(ans) - k, end(ans)));

  for (int i = 0; i < n; ++i)
    cout << ans[i] << " \n"[i == n - 1];

  return 0;
}
