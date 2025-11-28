#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<int> w(n);
  for (int &i : w) cin >> i;

  sort(begin(w), end(w), greater<int>());

  for (int i = 0; i < (int) w.size(); ++i) {
    if (i + 1 < (int) w.size() and w[i] + w.back() <= m)
      w.pop_back();
  }

  cout << w.size() << '\n';

  return 0;
}
