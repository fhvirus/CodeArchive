#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  double ans = 0, two = 1, last = 0;
  for (int i = 1; i <= 50; ++i) {
    double cur = pow(1 - two / 2, M - 1) * pow(1 - two, N - M);
    ans += two * (cur - last);
    last = cur, two /= 2;
  }

  cout << setprecision(9) << fixed << ans << '\n';

  return 0;
}
