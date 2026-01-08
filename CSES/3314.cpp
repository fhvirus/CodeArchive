#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> h(n);
  for (int &i : h) cin >> i;
  h.push_back(INT_MAX);

  vector<pair<int, int>> stk;
  stk.emplace_back(INT_MAX, 0);

  for (int i : h) {
    int dep = 0;
    while (stk.back().first < i) {
      auto [h, t] = stk.back();
      dep = max(dep, t + 1);
      stk.pop_back();
      if (stk.back().first > h)
        stk.back().second = max(stk.back().second, t + 1);
    }
    stk.emplace_back(i, dep);
  }

  cout << stk.back().second << '\n';
  
  return 0;
}
