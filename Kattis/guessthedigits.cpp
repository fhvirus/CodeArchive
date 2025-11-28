#include <bits/stdc++.h>
using namespace std;

void impossible() { cout << "IMPOSSIBLE\n"; exit(0); }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int64_t m, n, p, q;
  cin >> m >> n >> p >> q;

  int len_p = (int) to_string(p).size();
  if (len_p > n) impossible();

  vector<int64_t> d(m);
  d[0] = p;
  int64_t carry = 0;
  for (int i = 0; i < m; ++i) {
    d[i] = d[i] * q + carry;
    carry = d[i] / 10;
    d[i] %= 10;
    if (i < m - n) d[i + len_p] = d[i];
  }

  if (carry != 0 or d[m - 1] == 0 or d[m - n - 1] == 0)
    impossible();

  reverse(begin(d), end(d));
  for (int64_t i : d) cout << i;
  cout << '\n';

  return 0;
}
