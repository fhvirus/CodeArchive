#include <bits/stdc++.h>
using namespace std;

bool ErdosGallai(vector<int>& d) {
  ranges::sort(d, greater());
  int n = (int)size(d), sum = 0, tail_sum = 0;
  for (int i = 0, j = n; i < n; ++i) {
    if (j <= i) tail_sum -= d[j++];
    while (j - 1 > i and d[j - 1] < (i + 1)) tail_sum += d[--j];
    sum += d[i];
    if (sum > (i + 1) * i + tail_sum + (i + 1) * (j - i - 1))
      return false;
  }
  return sum % 2 == 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n; cin >> n, n != 0; ) {
    vector<int> d(n);
    for (int &i : d) cin >> i;
    cout << (ErdosGallai(d) ? "yes\n" : "no\n");
  }

  return 0;
}
