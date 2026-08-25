#include "lib1405.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  int s = 2 * (n + m);
  vector<int> des(1 + s), top(1 + m);
  for (int i = 1; i <= s; ++i) cin >> des[i];
  for (int j = 1; j <= m; ++j) top[j] = s + 1 - j;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1, last = 0; j <= m; ++j) {
      int d = des[top[j]];
      bool need = (d == i or (last != 0 and d <= n + last));
      if (need) {
        if (last != 0) top[last] = top[j];
        top[j] = s - m + 1 - i;
        last = j;
      }
      Report(need);
    }
  }

  return 0;
}
