#include <bits/stdc++.h>
using namespace std;

int64_t solve(int64_t x) {
  if (x < 10) return x + 1;
  string s = to_string(x);
  int n = (int) s.size();
  int64_t pow9 = 1, ans = 1;
  for (int i = 1; i < n; ++i) pow9 *= 9;
  for (int i = 0; i <= n; ++i) {
    if (i == n) {
      ans += 1;
      break;
    }
    int64_t t = (s[i] - '0') - (i > 0 and s[i - 1] < s[i]) - (i == 0);
    ans += t * pow9;
    pow9 /= 9;
    if (i > 0 and s[i - 1] == s[i]) break;
  }
  pow9 = 1;
  for (int i = 1; i < n; ++i) {
    pow9 *= 9;
    ans += pow9;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int64_t a, b;
  cin >> a >> b;

  cout << solve(b) - solve(a - 1) << '\n';

  return 0;
}
