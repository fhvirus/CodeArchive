#include <bits/stdc++.h>
using namespace std;

const int kN = 10000;
int X[kN];

// Erdős-Gallai theorem
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int N, t = 1; cin >> N, N != 0; ++t) {
    for (int i = 0; i < N; ++i)
      cin >> X[i];
    sort(X, X + N, greater());
    int sum = 0, tail_sum = 0, ans = true;
    for (int i = 0, j = N; i < N and ans; ++i) {
      if (j <= i) tail_sum -= X[j++];
      while (j - 1 > i and X[j - 1] < (i + 1)) tail_sum += X[--j];
      sum += X[i];
      if (sum > (i + 1) * i + tail_sum + (i + 1) * (j - i - 1))
        ans = false;
    }
    if (sum % 2 != 0) ans = false;
    cout << "Case #" << t << (ans ? ":Yes\n" : ":No\n");
  }

  return 0;
}
