#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int p, q;
  cin >> p >> q;

  for (int64_t r = 1; r <= 1'000'000; ++r) {
    int64_t n = q - p;
    int64_t a = p, b = -p - 2 * r * n, c = (r * r - r) * p;
    int64_t d = b * b - 4 * a * c;
    if (d < 0) continue;
    int64_t sq_d = int64_t(round(sqrt(d)));
    if (sq_d * sq_d != d) continue;
    for (auto k : {sq_d, -sq_d}) {
      int64_t g = (-b + k) / (2 * a);
      if (g < r or g * 2 * a != (-b + k)) continue;
      cout << r << ' ' << g << '\n';
      exit(0);
    }
  }
  cout << "impossible\n";

  return 0;
}
