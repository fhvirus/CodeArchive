#include <bits/stdc++.h>
using namespace std;

typedef vector<int8_t> board;
const int dir[5] = {0, 1, 0, -1, 0};

int PermToInt(auto& v) {
  int use = 0, i = 0, r = 0;
  for (auto x : v) r = r * ++i + __builtin_popcount(use & -(1<<x)),
    use |= 1 << x;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  board start(9);
  iota(begin(start), end(start), 1);
  start[8] = 0;

  bitset<362880> easy;
  vector<board> cur, nxt;
  easy[PermToInt(start)] = 1, cur.push_back(start);
  for (int dis = 1; dis <= 20 and not empty(cur); ++dis) {
    nxt.clear();
    for (auto u : cur) {
      int z = (int) (ranges::find(u, 0) - begin(u));
      int i = z / 3, j = z % 3;
      for (int d : {0, 1, 2, 3}) {
        int ni = i + dir[d], nj = j + dir[d + 1];
        if (0 <= min(ni, nj) and max(ni, nj) < 3) {
          swap(u[z], u[ni * 3 + nj]);
          int id = PermToInt(u);
          if (not easy[id]) {
            easy[id] = 1;
            if (dis < 20) nxt.push_back(u);
          }
          swap(u[z], u[ni * 3 + nj]);
        }
      }
    }
    swap(cur, nxt);
  }

  int k;
  cin >> k;
  while (k --> 0) {
    board a(9);
    for (auto &i : a) { int t; cin >> t; i = (int8_t) t; }
    cout << (easy[PermToInt(a)] ? "Easy\n" : "Hard\n");
  }

  return 0;
}
