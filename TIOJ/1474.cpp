#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, ans = 0;
  cin >> n >> ws;

  vector blocks(n, vector<vector<int8_t>>());
  for (int i = 0; i < n; ++i) {
    vector<int8_t> blk;
    string line; getline(cin, line);
    for (stringstream ss(line); ss; ) {
      int v; ss >> v >> ws;
      blk.emplace_back(v);
    }
    blocks[i].push_back(blk);
    ranges::reverse(blk);
    blocks[i].push_back(blk);
    if (blk[0] < blk.back())
      ranges::reverse(blk);

    bool decreasing = true;
    for (int j = 1; j < (int)size(blk); ++j)
      decreasing &= (blk[j] < blk[j - 1]);
    if (not decreasing) continue;
    vector<int8_t> a(blk[0]);
    for (int h : blk) for (int j = 0; j < h; ++j) a[j] += 1;
    blocks[i].push_back(a);
    ranges::reverse(a);
    blocks[i].push_back(a);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      bool can = false;
      for (const auto &bi : blocks[i]) {
        int si = (int)size(bi);
        for (const auto &bj : blocks[j]) {
          int sj = (int)size(bj);
          for (int d = 0; d <= si; ++d) {
            bool all_same = true;
            int h0 = bi[0] + (d == 0 ? bj[0] : 0), len = max(si, d + sj);
            for (int k = 0; k < len and all_same; ++k) {
              int h = (k < si ? bi[k] : 0) + (d <= k and k < d + sj ? bj[k - d] : 0);
              all_same &= (h == h0);
            }
            if (all_same) {
              ans = max(ans, h0 * len);
              can = true;
              break;
            }
          }
          if (can) break;
        }
        if (can) break;
      }
    }
  }
  cout << ans << '\n';

  return 0;
}
