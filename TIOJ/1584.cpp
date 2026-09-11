#include <bits/stdc++.h>
using namespace std;

void solve() {
  int H, W, HP, G;
  cin >> H >> W >> HP >> G;

  vector<string> g(H);
  int di, dj;
  for (int i = 0; i < H; ++i) {
    cin >> g[i];
    auto p = g[i].find('D');
    if (p != string::npos) di = i, dj = (int) p;
  }

  vector<int> cnt(H + W - 1);
  for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j)
    if (g[i][j] == 'e') cnt[abs(i - di) + abs(j - dj)] += 1;

  int ans = 0;
  for (int dis = 0; dis < H + W - 1 and HP - dis > 0 and HP - dis * 2 + G > 0; ++dis)
    for (int i = 0; i < cnt[dis] and HP - dis > 0 and HP - dis * 2 + G > 0; ++i)
      HP += G - dis * 2, ++ans;
  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
