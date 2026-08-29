#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) {
    int N;
    cin >> N;

    string s;
    cin >> s;

    bool ans = (N > 1 and (s[0] != s[1] or s[N-1] != s[N-2]));
    for (int i = 3; i < N; ++i)
      ans |= (s[i] != s[i - 1] and s[i - 2] != s[i - 3]);
    puts(ans ? "YES" : "NO");
  }

  return 0;
}
