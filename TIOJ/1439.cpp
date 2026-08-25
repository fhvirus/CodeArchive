#include <bits/stdc++.h>
using namespace std;

int last_mid_le_p(int p, int m, int t, int nl, int nr) {
  int res = nl - 1;
  for (int l = 1 << __lg(nr - nl + 1); l > 0; l /= 2) if (res + l <= nr) {
    int tl = 0, tr = res + l - 1;
    for (int i = 0; i < t; ++i) {
      int mid = (tl + tr) / 2;
      if (m >> i & 1) tl = mid + 1;
      else tr = mid - 1;
    }
    if ((tl + tr) / 2 <= p) res += l;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int p, q;
  cin >> p >> q;

  int lim = p * 2 + 1;
  for (int i = 0; i < q; ++i) lim = (lim + 1) * 2 + 1;
  lim += 1;

  vector<pair<int, int>> ans;
  for (int m = 0; m < (1 << (q - 1)); ++m) {
    int nl = p + 1, nr = lim;
    for (int i = 0; i < q - 1 and nl <= nr; ++i) {
      if (m >> i & 1) nr = last_mid_le_p(p - 1, m, i, nl, nr);
      else nl = last_mid_le_p(p, m, i, nl, nr) + 1;
    }
    if (nl <= nr) nl = last_mid_le_p(p - 1, m, q - 1, nl, nr) + 1;
    if (nl <= nr) nr = last_mid_le_p(p, m, q - 1, nl, nr);
    if (nl <= nr) ans.emplace_back(nl, nr);
  }

  ranges::sort(ans);
  int s = 0;
  for (int i = 1; i < (int)size(ans); ++i) {
    if (ans[i].first > ans[s].second + 1)
      ans[++s] = ans[i];
    else ans[s].second = ans[i].second;
  }
  ans.resize(s + 1);

  cout << size(ans) << '\n';
  for (auto [l, r] : ans)
    cout << l << ' ' << r << '\n';

  return 0;
}
