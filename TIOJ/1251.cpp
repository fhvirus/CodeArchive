#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  const int kN = 1'000'000;

  vector<int> a;
  for (int i = 1; i <= kN; i += 2) a.push_back(i);
  for (int i = 1; i < (int)size(a) and a[i] < (int)size(a); ++i) {
    int t = a[i];
    vector<int> b;
    for (int j = 0; j < (int)size(a); j += t)
      for (int k = 0; k < t - 1 and j + k < (int)size(a); ++k)
        b.push_back(a[j + k]);
    swap(a, b);
    b.clear();
  }

  for (int N; cin >> N, N != 0; )
    cout << (ranges::upper_bound(a, N) - begin(a)) << '\n';

  return 0;
}
