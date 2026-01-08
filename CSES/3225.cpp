// Fermat polygonal number theorem where n = 3
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> sa(n + 1), rank(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> sa[i];
    rank[sa[i]] = i;
  }

  string s(n, ' ');
  char c = s[sa[1] - 1] = 'a';
  for (int i = 1; i < n; ++i) {
    int u = sa[i], v = sa[i + 1];
    int rnu = rank[u == n ? 0 : u + 1], rnv = rank[v == n ? 0 : v + 1];
    if (rnu > rnv) c += 1;
    if (c > 'z') {
      s = "-1";
      break;
    }
    s[v - 1] = c;
  }

  cout << s << '\n';

  return 0;
}
