#include <bits/stdc++.h>
using namespace std;

#include "lib1172.h"

void query(int n, int d[], int l, int ans[]) {
  vector<int> id(n);
  iota(begin(id), end(id), 0);
  shuffle(begin(id), end(id), mt19937(random_device{}()));

  const auto solve = [&](const auto& solve, int dl, int dr, int lb, int rb) -> void {
    int target = dl;
    for (int i = dl + 1; i <= dr; ++i)
      if (max(d[i] - lb, rb - d[i]) < max(d[target] - lb, rb - d[target]))
        target = i;
    nth_element(begin(id) + lb, begin(id) + d[target], begin(id) + rb, comp);
    ans[target] = id[d[target]];
    if (dl < target) solve(solve, dl, target - 1, lb, d[target]);
    if (target < dr) solve(solve, target + 1, dr, d[target] + 1, rb);
  };

  solve(solve, 0, l - 1, 0, n);
}
