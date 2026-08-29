#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  boost::multiprecision::cpp_int num = 1, x = 2;
  for (int t = N - 1; t > 0; x *= x, t /= 2)
    if (t & 1) num = num * x;
  cout << num << '\n';

  vector<double> h(N);
  vector<int> oth;
  double last = 0;
  for (int i = 0; i < N; ++i) {
    cin >> h[i];
    if (h[i] > last) {
      cout << i + 1 << '\n';
      last = h[i];
    } else oth.push_back(i);
  }

  ranges::sort(oth, [&](int u, int v) { return h[u] > h[v]; });
  for (int i : oth) cout << i + 1 << '\n';

  return 0;
}
