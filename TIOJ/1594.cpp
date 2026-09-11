#include <bits/stdc++.h>
using namespace std;

const int mod = 11;
int C[mod][mod];
int get_C(int a, int b) {
  int ans = 1;
  while (a > 0 or b > 0) {
    ans = ans * C[a % mod][b % mod] % mod;
    a /= mod, b /= mod;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  C[0][0] = 1;
  for (int i = 1; i < mod; ++i)
    for (int j = 0; j <= i; ++j)
      C[i][j] = (C[i-1][j] + (j > 0 ? C[i-1][j-1] : 0)) % mod;

  int T;
  cin >> T;
  while (T --> 0) {
    int n; cin >> n;
    cout << (get_C(n, n / 2) - get_C(n, n / 2 + 1) + mod) % mod << '\n';
  }

  return 0;
}
