#include <bits/stdc++.h>
using namespace std;

// 0 1 2 9
// 3 4 5 A
// 6 7 8 B
int last_col(int r, auto& row, auto& cnt) {
  if (r == 2) return 1;
  int need = row[r] % 2, ans = 0;
  for (int v : {need, need + 2, need + 4}) if (cnt[v] > 0) {
    cnt[v] -= 1;
    ans += last_col(r + 1, row, cnt);
    cnt[v] += 1;
  }
  return ans;
}
int last_row(int c, auto& col, auto& row, auto& cnt) {
  if (c == 3) return last_col(0, row, cnt);
  int need = (3 - col[c] % 3) % 3;
  int ans = 0;
  for (int v : {need, need + 3}) if (cnt[v] > 0) {
    cnt[v] -= 1;
    ans += last_row(c + 1, col, row, cnt);
    cnt[v] += 1;
  }
  return ans;
}
int pick(int i, int j, int had, auto& col, auto& row, auto& cnt) {
  if (j == 6) i += 1, j = 0;
  while (i < 6 and cnt[i] == 0) ++i, j = 0;
  if (i == 6) return (had == 0b111111 ? last_row(0, col, row, cnt) : 0);
  int ans = 0, left = 0b111111 ^ had;
  for (; j < 6; ++j) if (left >> j & 1) {
    cnt[i] -= 1;
    col[j % 3] += i, row[j / 3] += i;
    left ^= (1 << j);

    ans += pick(i, j + 1, had | (1 << j), col, row, cnt);

    left ^= (1 << j);
    col[j % 3] -= i, row[j / 3] -= i;
    cnt[i] += 1;
  }
  ans += pick(i + 1, 0, had, col, row, cnt);
  return ans;
}

void solve() {
  vector<int> cnt(6, 0), col(4, 0), row(3, 0);
  int tot = 0, mnv = 6;
  for (int i = 0; i < 12; ++i) {
    int v = 0;
    string s; cin >> s;
    for (char c : s) v = (v * 10 + (c - '0')) % 6;
    cnt[v] += 1;
    tot += v, mnv = min(mnv, v);
  }
  if (tot % 6 != 0) {
    cout << 0 << '\n';
    return;
  }

  col[0] = row[0] = mnv;
  cnt[mnv] -= 1;

  int ans = pick(mnv, 1, 0b1, col, row, cnt);
  for (int i : cnt)
    for (int j = 1; j <= i - (i == mnv); ++j)
      ans *= j;

  cout << ans / 12 << '\n';
  return;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  solve();
  solve();

  return 0;
}
