#include <bits/stdc++.h>
using namespace std;

struct Ad { int l, u, r, d; char c; };

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int C;
  cin >> C;
  while (C --> 0) {
    int H, W, N;
    cin >> H >> W >> N;

    vector<Ad> ad(N);
    for (auto &[l, u, r, d, c] : ad)
      cin >> l >> u >> r >> d >> c;

    string s(W, 'o');
    for (int i = 1; i <= H; ++i) {
      ranges::fill(s, 'o');
      for (int k = 0; k < N; ++k)
        if (ad[k].u <= i and i <= ad[k].d)
          for (int j = ad[k].l; j <= ad[k].r; ++j)
            s[j - 1] = ad[k].c;
      cout << s << '\n';
    }
    cout << '\n';
  }

  return 0;
}
