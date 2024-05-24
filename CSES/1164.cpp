#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<pair<int, int>> es;
  for (int a, b, i = 1; i <= n; ++i) {
    cin >> a >> b;
    es.emplace_back(a, i);
    es.emplace_back(b + 1, -i);
  }

  sort(begin(es), end(es));

  vector<int> ans(n + 1);
  vector<int> buf(n);
  for (int i = 0; i < n; ++i) buf[i] = n - i;
  for (auto [t, i] : es) {
    if (i < 0) {
      buf.push_back(ans[-i]);
    } else {
      ans[i] = buf.back();
      buf.pop_back();
    }
  }

  cout << *max_element(begin(ans), end(ans)) << '\n';
  for (int i = 1; i <= n; ++i)
    cout << ans[i] << " \n"[i == n];

  return 0;
}
