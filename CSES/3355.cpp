#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;

  unordered_map<int, int> mp;
  while (t --> 0) {
    int n;
    cin >> n;
    for (int i = 0, ok = 1; ok and i * i <= n; ++i) {
      for (int j = 0; j <= i; ++j) {
        int v = i * i + j * j;
        mp[v] = i << 16 | j;
        if (mp.count(n - v)) {
          ok = 0;
          int t = mp.at(n - v);
          cout << i << ' ' << j << ' ' << (t >> 16) << ' '
            << (t & 0xffff) << '\n';
          break;
        }
      }
    }
  }

  return 0;
}
