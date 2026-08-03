#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  const int kN = 10;
  vector<int> max_len(kN + 1, 1);
  for (int i = 2; i <= kN; ++i)
    max_len[i] = max_len[i - 1] / gcd(max_len[i - 1], i) * i;

  vector<int> mask(max_len[kN]);
  for (int i = 0; i < max_len[kN]; ++i)
    for (int j = 0; j < kN; ++j)
      if ((i + 1) % (j + 1) == 0)
        mask[i] |= (1 << j);

  for (int P, N, M, t = 0; cin >> P >> N >> M, P != 0; ++t) {
    vector<string> anss;
    int n = min(P, max_len[N]);
    string s(n, '1');
    if (M % 2 == 0) anss.push_back(s);
    for (int cnt = 2 - M % 2; cnt <= min(M, N); cnt += 2) {
      for (int x = (1 << cnt) - 1; x < (1 << N); ) {
        for (int i = 0; i < n; ++i)
          s[i] = char('1' - popcount((unsigned)(mask[i] & x)) % 2);
        anss.push_back(s);
        { int c = x & -x, r = x + c; x = (((r ^ x) >> 2) / c) | r; }
      }
    }
    ranges::sort(anss);
    if (t) cout << '\n';
    for (auto &i : anss) {
      int len = P;
      for (; len >= max_len[N]; len -= max_len[N]) cout << i;
      cout << i.substr(0, len) << '\n';
    }
  }

  return 0;
}
