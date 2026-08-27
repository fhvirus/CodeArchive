#include <bits/stdc++.h>
using namespace std;

constexpr uint64_t digits[5] = {
  0b0100111011101010111011101110111011101110000000000000ul,
  0b1100001000101010100010000010101010101010010000001110ul,
  0b0100111011101110111011100010111011101010111011100000ul,
  0b0100100000100010001010100010101000101010010000001110ul,
  0b1110111011100010111011100010111011101110000000000000ul,
};
void verify() {
  for (auto i : digits) {
    for (int j = 51; j >= 0; --j)
      cout << ((i >> j & 1) ? "##" : "  ");
    cout << endl;
  }
}

auto get_w(int i, int m, int gm) {
  // [i * gm / m, (i + 1) * gm / m]
  int gu = i * gm / m, gd = (i + 1) * gm / m;
  if (gu == gd or gd * m == (i + 1) * gm) return tuple(gu, gu, 1, 0);
  return tuple(gu, gd, gd * m - i * gm, (i + 1) * gm - gd * m);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int c, m, n, t = 1; cin >> c >> m >> n, c != 0; ++t) {
    const int gm = 5, gn = c * 4 - 1;
    string s; cin >> s;
    vector g(gm, vector<bool>(gn, false));
    for (int i = 0; i < c; ++i) {
      int p = (int) "1234567890+-="s.find(s[i]);
      for (int ci : {0, 1, 2, 3, 4})
        for (int cj : {0, 1, 2})
          g[ci][4 * i + cj] = (digits[ci] >> (51 - (p * 4 + cj)) & 1);
    }

    cout << "Case #" << t << ":\n";
    for (int i = 0; i < m; ++i) {
      auto [gu, gd, wu, wd] = get_w(i, m, gm);
      for (int j = 0; j < n; ++j) {
        auto [gl, gr, wl, wr] = get_w(j, n, gn);
        int tot = (wu + wd) * (wl + wr);
        int sum = (g[gu][gl] * wu * wl + g[gu][gr] * wu * wr +
            g[gd][gl] * wd * wl + g[gd][gr] * wd * wr);
        cout << "-*"[sum * 10 >= tot * 4];
      }
      cout << '\n';
    }
  }

  return 0;
}
