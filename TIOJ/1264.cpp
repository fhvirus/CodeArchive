#include <bits/stdc++.h>
using namespace std;

int solve(int n, int m) {
  if (n > m) swap(n, m);
  if (n == 1) return abs(m % 4 - 1); // 1 0 1 2 ...
  if (n % 2 == 1) return 0;
  // n even, cycle: n + 1
  m %= n + 1;
  if (m == n) return 4;
  return m == n - 2 or m == 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;
  cout << solve(n, k) << endl;

  return 0;
}
