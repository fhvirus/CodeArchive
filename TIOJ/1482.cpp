#include <bits/stdc++.h>
using namespace std;

set<int> vis;
int dfs(int n, uint32_t state, int cnt) {
  if (vis.count(state)) return cnt;
  vis.insert(state);
  int res = cnt;
  for (int i = 0; i + 2 < n; ++i) {
    if ((state >> i & 0b111) == 0b011)
      res = min(res, dfs(n, (state & ~(0b111 << i)) | (0b100 << i), cnt - 1));
    if ((state >> i & 0b111) == 0b110)
      res = min(res, dfs(n, (state & ~(0b111 << i)) | (0b001 << i), cnt - 1));
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n; cin >> n; ) {
    string s; cin >> s;
    uint32_t state = 0;
    for (int i = 0; i < n; ++i)
      state |= (s[i] == 'o') << i;

    vis.clear();
    cout << dfs(n, state, popcount(state)) << '\n';
  }

  return 0;
}
