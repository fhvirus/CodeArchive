#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kC = 1'000'000;

  int n;
  cin >> n;

  vector<pair<int, int>> pts(n);
  for (auto &[x, y] : pts)
    cin >> x >> y;

  int tot = 0;
  int64_t ans[2] {0, 0};
  for (int i = 0; i < n; ++i) {
    int pos = i;
    for (; pos > 0 and pts[pos - 1] > pts[pos]; --pos)
      swap(pts[pos], pts[pos - 1]);
    
    vector<pair<int, int>> ld, lu, rd, ru;
    for (int j = pos - 1; j >= 0; --j) {
      if (pts[j].second < pts[pos].second) {
        if (ld.empty() or ld.back().second < pts[j].second)
          ld.push_back(pts[j]);
      } else {
        if (lu.empty() or lu.back().second > pts[j].second)
          lu.push_back(pts[j]);
      }
    }
    for (int j = pos + 1; j <= i; ++j) {
      if (pts[j].second < pts[pos].second) {
        if (rd.empty() or rd.back().second < pts[j].second)
          rd.push_back(pts[j]);
      } else {
        if (ru.empty() or ru.back().second > pts[j].second)
          ru.push_back(pts[j]);
      }
    }

    int delta = int(size(ld) + size(lu) + size(rd) + size(ru));
    for (int j = 0, plu = -1, prd = 0, qh = 0, qt = 0; j < size(ld); ++j) {
      while (plu + 1 < size(lu) and lu[plu + 1].first > ld[j].first) ++plu;
      while (prd < size(rd) and rd[prd].second < ld[j].second) ++prd;
      int ub = (plu < 0 ? kC + 1 : lu[plu].second);
      int rb = (prd >= size(rd) ? kC + 1 : rd[prd].first);
      while (qt < size(ru) and ru[qt].first < rb) ++qt;
      while (qh < qt and ru[qh].second > ub) ++qh;
      delta -= qt - qh;
    }
    for (int j = 0, pld = -1, pru = 0, qh = 0, qt = 0; j < size(lu); ++j) {
      while (pld + 1 < size(ld) and ld[pld + 1].first > lu[j].first) ++pld;
      while (pru < size(ru) and ru[pru].second > lu[j].second) ++pru;
      int db = (pld < 0 ? -kC - 1 : ld[pld].second);
      int rb = (pru >= size(ru) ? kC + 1 : ru[pru].first);
      while (qt < size(rd) and rd[qt].first < rb) ++qt;
      while (qh < qt and rd[qh].second < db) ++qh;
      delta -= qt - qh;
    }

    tot += delta;
    ans[i & 1] += tot;
  }

  cout << ans[0] << ' ' << ans[1] << '\n';

  return 0;
}
