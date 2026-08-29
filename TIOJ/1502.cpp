#include <bits/stdc++.h>
using namespace std;

auto FailFunction(const string& s) {
  vector<int> f(size(s));
  for (int i = 1; i < (int)size(s); ++i) {
    int j = f[i - 1];
    while (j > 0 and s[j] != s[i]) j = f[j - 1];
    f[i] = j + (s[i] == s[j]);
  }
  return f;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s, t;
  getline(cin, s);
  getline(cin, t);

  int si = 0, ti = 0;
  for (; si < (int)size(s) and ti < (int)size(t); ) {
    if (t[ti] == '*') { ++ti; ++si; continue; }
    int to = ti + 1;
    while (to < (int)size(t) and t[to] != '*') ++to;
    auto f = FailFunction(t.substr(ti, to - ti));
    for (int j = 0; si < (int)size(s) and j < to - ti; ++si) {
      while (j > 0 and s[si] != t[ti + j]) j = f[j - 1];
      j += (s[si] == t[ti + j]);
    }
    ti = to;
  }

  cout << (ti == (int)size(t) ? "Asssssss!!!!!\n" : "zzz...\n");

  return 0;
}
