#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int c;
  cin >> c;

  while (c --> 0) {
    int n, t, m;
    cin >> n >> t >> m;

    vector<int> tid(m);
    array<queue<int>, 2> bank;

    for (int i = 0; i < m; ++i) {
      string side;
      cin >> tid[i] >> side;
      bank[side == "right"].push(i);
    }

    int cur_t = 0, cur_b = 0;
    while (not empty(bank[0]) or not empty(bank[1])) {
      int next_car = INT_MAX;
      for (int i : {0, 1}) if (not empty(bank[i]))
        next_car = min(next_car, tid[bank[i].front()]);
      cur_t = max(cur_t, next_car);

      auto &b = bank[cur_b];
      for (int j = 0; j < n and !empty(b) and tid[b.front()] <= cur_t; ++j) {
        tid[b.front()] = cur_t + t;
        b.pop();
      }

      cur_t += t;
      cur_b ^= 1;
    }

    for (int i : tid) cout << i << '\n';
    cout << '\n';
  }

  return 0;
}
