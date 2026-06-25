#include <bits/stdc++.h>
using namespace std;

void solve() {
  int r, c;
  cin >> r >> c;

  cin.ignore();
  vector<string> g(2 * r + 1);
  for (auto &i : g) getline(cin, i);

  const auto update = [](map<int, int>& mp, int key, int val) {
    auto it = mp.find(key);
    if (it == end(mp)) mp[key] = val;
    else it->second = min(it->second, val);
  };
  const auto cost = [&g](int i, int j, int d) {
    return (d & 1 ? g[i * 2 + 2][j * 2 + 1] - '0' : 0) +
      (d & 2 ? g[i * 2 + 1][j * 2 + 2] - '0' : 0);
  };
  const auto get = [](int a, int i) { return (a >> (2 * i)) & 0b11; };
  const auto modify = [](int a, int i, int v) { return (a & ~(0b11 << (2 * i))) | (v << (2 * i)); };
  const auto connect = [&c, &get, &modify](int a, int p) {
    static vector<int> stk; stk.clear();
    int r = modify(modify(a, p, 0), p + 1, 0);
    for (int i = 0; i < c; ++i) {
      int t = get(a, i);
      if (t == 0) continue;
      if (t == 1) stk.push_back(i);
      else {
        if (stk.back() == p + 1) return modify(r, i, 1);
        if (i == p) return modify(r, stk.back(), 2);
        stk.pop_back();
      }
    }
    assert(false);
    return -1;
  };

  map<int, int> sc;
  sc[0] = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      map<int, int> dp;
      for (auto [state, val] : sc) {
        int a = get(state, j), b = get(state, j + 1);
        if (a == 0 and b == 0) // -- -> ()
          update(dp, modify(modify(state, j, 1), j + 1, 2), val + cost(i, j, 0b11));
        else if (a == 0 or b == 0) { // -?, ?- -> -?, ?-
          update(dp, state, val + cost(i, j, (a != 0) + 2 * (b != 0)));
          update(dp, modify(modify(state, j, b), j + 1, a), val + cost(i, j, (b != 0) + 2 * (a != 0)));
        } else {
          if (a != b) { // 12 -> 00 if last corner, 21 -> 00
            if (a == 1 and b == 2 and not (i == r - 1 and j == c - 1)) continue;
            update(dp, modify(modify(state, j, 0), j + 1, 0), val);
          } else // 11, 22 -> 00, find them
            update(dp, connect(state, j), val);
        }
      }
      dp.swap(sc);
    }
    { // next row
      map<int, int> dp;
      for (auto [state, val] : sc) if (get(state, c) == 0)
        update(dp, state << 2, val);
      dp.swap(sc);
    }
  }
  cout << sc[0] << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  while (n --> 0) solve();

  return 0;
}
