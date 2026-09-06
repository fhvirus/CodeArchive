#include <bits/stdc++.h>
using namespace std;

int64_t Fibonacci(int64_t n) {
  int64_t a = 0, b = 1;
  for (auto l = __lg(n); l >= 0; --l) {
    tie(a, b) = pair(a * (2 * b - a), a * a + b * b);
    if (n >> l & 1) tie(a, b) = pair(b, a + b);
  }
  return a;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n; cin >> n; )
    cout << Fibonacci(n + 2) << '\n';

  return 0;
}
