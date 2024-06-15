#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> x(n + 1, 0);
  for (int i = 1; i <= n; ++i)
    cin >> x[i];

  vector<int> stk(1, 0);
  for (int i = 1; i <= n; ++i) {
    while (x[stk.back()] >= x[i])
      stk.pop_back();
    cout << stk.back() << " \n"[i == n];
    stk.push_back(i);
  }

  return 0;
}
