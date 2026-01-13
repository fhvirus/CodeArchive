#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kL = 30;

  int n, k;
  cin >> n >> k;

  vector<int> basis(kL);
  int non = 0;
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    for (int l = kL - 1; l >= 0; --l)
      if (x >> l & 1) x ^= basis[l];
    if (x != 0) basis[__lg(x)] = x;
    else non += 1;
  }

  vector<int> ans(min((1 << min(non, __lg(k - 1) + 1)), k), 0);
  for (int b : basis) if (b != 0) {
    int s = int(size(ans));
    for (int i = 0; i < s; ++i) ans.push_back(ans[i] ^ b);
    sort(begin(ans) + s, end(ans));
    if (2 * s >= k) {
      ans.resize(k);
      break;
    }
  }

  for (int i = 0; i < k; ++i)
    cout << ans[i] << " \n"[i == k - 1];

  return 0;
}
