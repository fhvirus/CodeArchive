#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kN = 100001;
  bitset<kN> ans;
  ans.set(0);

  int n;
  cin >> n;

  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    ans = ans | ans << x;
  }

  cout << ans.count() - 1 << '\n';
  for (int i = (int) ans._Find_next(0); i < kN; ) {
    cout << i;
    cout << " \n"[(i = (int) ans._Find_next(i)) >= kN];
  }


  return 0;
}
