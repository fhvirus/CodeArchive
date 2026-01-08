#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> a(N + 1);
  for (int i = 1; i <= N; ++i) cin >> a[i];
  partial_sum(begin(a), end(a), begin(a));

  vector<int> dpr(N + 1, INT_MIN), dpl(N + 1, INT_MIN);
  dpr[1] = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j < i; ++j) {
      dpr[i] = max(dpr[i], dpr[j] + (a[i - 1] - a[j - 1]) * (a[N] - a[i - 1]));
      dpl[i] = max(dpl[i], dpl[j] + (a[i] - a[j]) * a[j]);
    }
    dpl[i] = max(dpl[i], dpr[i] - a[i - 1] * (a[N] - a[i]));
  }

  cout << dpl[N] << '\n';
  
  return 0;
}
