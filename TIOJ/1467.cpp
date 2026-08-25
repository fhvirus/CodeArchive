#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int64_t n; cin >> n; ) {
    int64_t t = n / 2;
    int64_t bad = (t * (t + 1) / 2 + t + 1) * 3;
    if (n % 2 == 0) bad -= 3;
    int64_t all = (n + 2) * (n + 1) / 2;
    cout << all - bad << '\n';
  }

  return 0;
}
