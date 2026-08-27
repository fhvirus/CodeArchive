#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m;
  cin >> m;

  // wtf is this (peeked solution)

  string a = "a", b = "b";
  for (int i = 0; i * (i + 1) / 2 < m; ++i)
    tie(a, b) = pair(a + b, b + a);

  cout << a << '\n' << b << '\n';

  return 0;
}
