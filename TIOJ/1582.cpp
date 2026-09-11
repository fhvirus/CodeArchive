#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;
  int n = (int)size(s);

  const auto get = [&](int &i) {
    if (not isdigit(s[i])) return 1;
    int val = 0;
    for (; i < n and isdigit(s[i]); ++i)
      val = val * 10 + (s[i] - '0');
    return val;
  };

  map<int, int> mp;
  for (int a = 1, b, i = 0; i < n; ) { // term := a * x^b
    a *= get(i), b = 0;
    if (i < n and s[i] == 'x') {
      b = 1, ++i;
      if (i < n and s[i] == '^') {
        i += 1;
        if (i < n and s[i] == '-')
          b = -1, ++i;
        b *= get(i);
      }
    }
    mp[b] += a;
    if (i == n) break;
    a = (s[i++] == '-' ? -1 : 1);
  }

  bool f = true;
  for (auto it = rbegin(mp); it != rend(mp); it = next(it)) {
    int a, b; tie(b, a) = *it;
    a *= b; b -= 1;
    if (a == 0) continue;
    if (not f and a > 0) cout << '+';
    if (a < 0) cout << '-';
    if (b == 0 or abs(a) != 1) cout << abs(a);
    if (b != 0) {
      cout << 'x';
      if (b != 1) cout << '^' << b;
    }
    f = false;
  }
  cout << '\n';

  return 0;
}
