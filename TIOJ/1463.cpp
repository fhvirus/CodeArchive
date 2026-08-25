#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (string s; cin >> s, s[0] != '0'; ) {
    uint32_t a = 0, b = 1, c;
    for (int i = 0; i < (int)size(s); ++i) {
      c = 0;
      if (s[i] != '0') c += b;
      if (i > 0 and s[i - 1] != '0' and
          (s[i - 1] - '0') * 10 + (s[i] - '0') <= 26)
        c += a;
      a = b; b = c;
    }
    cout << b << '\n';
  }

  return 0;
}
