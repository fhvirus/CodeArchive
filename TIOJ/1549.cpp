#include <bits/stdc++.h>
using namespace std;

int64_t cost(int64_t a, int64_t b) { return (a - b) * (a - b); }

const int kN = 2'000'000;
int stk[kN], top = 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int64_t ans = 0;
  for (int a, i = 0; i < n; ++i) {
    cin >> a;
    while (stk[top-1] > a) {
      --top;
      ans += cost(stk[top], max(a, stk[top-1]));
    }
    stk[top++] = a;
  }
  for (int i = 1; i + 1 < top; ++i)
    ans += cost(stk[i], stk[i + 1]);

  cout << ans << '\n';

  return 0;
}
