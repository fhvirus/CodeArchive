#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, x;
  cin >> n >> x;

  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first;
    a[i].second = i + 1;
  }

  sort(begin(a), end(a));

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1, k = n - 1; j < k; ++j) {
      while (k > j and a[i].first + a[j].first + a[k].first > x) --k;
      if (k == j) break;
      if (a[i].first + a[j].first + a[k].first == x) {
        cout << a[i].second << ' ' << a[j].second << ' ' << a[k].second << '\n';
        exit(0);
      }
    }
  }

  cout << "IMPOSSIBLE\n";


  return 0;
}
