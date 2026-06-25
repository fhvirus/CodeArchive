#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int M, N;
  cin >> M >> N;

  vector<int> a(N);
  for (int &i : a) cin >> i;

  int lim = 2e9;
  for (int l = 1 << 30; l > 0; l /= 2) if (lim - l >= 0) {
    int t = lim - l;
    int64_t need = 0;
    for (int i : a) need += max(0, i - t);
    if (need <= M) lim -= l;
  }

  for (int &i : a) {
    int t = min(lim, i);
    M -= i - t;
    i = t;
  }
  int max_v = *ranges::max_element(a);
  for (int &i : a)
    if (i == max_v and M > 0 and i > 0)
      i -= 1, M -= 1;

  int64_t ans = 0;
  for (int i : a)
    ans += int64_t(i) * i;

  cout << ans << '\n';

  return 0;
}
