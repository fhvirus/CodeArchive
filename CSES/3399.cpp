#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;

  while (t --> 0) {
    int n, a, b;
    cin >> n >> a >> b;

    if (((a > 0) xor (b > 0)) or a + b > n) {
      cout << "NO\n";
      continue;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; ++i)
      cout << i << " \n"[i == n];
    for (int i = 1; i <= (n - a - b); ++i) cout << i << ' ';
    for (int i = b - 1; i >= 0; --i) cout << n - i << ' ';
    for (int i = 1; i <= a; ++i) cout << (n - a - b) + i << ' ';
    cout << '\n';
  }

  return 0;
}
