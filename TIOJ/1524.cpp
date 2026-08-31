#include <bits/stdc++.h>
using namespace std;

void report(uint64_t i, uint64_t n, const char* s) {
  while (i > n) i -= n;
  printf("Player %lu: \"%s\"\n", i, s);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vector<uint64_t> f {0, 1};
  while (f.back() <= (1ull << 63) - 1)
    f.push_back(2 * f.back() + size(f) + 1);

  int T;
  cin >> T;
  while (T --> 0) {
    uint64_t n, k;
    cin >> n >> k;

    vector<uint64_t> a(size(f));
    uint64_t lap = 0;
    int as = -1;
    for (int i = (int)size(f) - 1; i >= 1; --i) {
      if (k == f[i] or (i == 1 and as == -1)) { report(i, n, "Hot dog!"); break; }
      if (k == f[i] - 1 and i != 1) as = i;
      if (f[i - 1] < k and k <= f[i - 1] + (i - 1)) {
        report(i - (k - (f[i - 1] + 1)), n, "What!?"); break; }

      a[i] = lap + (k >= f[i] - 1);
      lap = lap * 2 + (k > f[i - 1]) + (k > f[i] - 2);
      if (k > f[i] - 2) k = 0;
      else if (k > f[i - 1] + (i - 1)) k -= f[i - 1] + (i - 1);
      else if (k > f[i - 1]) k = 0;
    }
    a[1] = 0;

    if (as != -1) {
      uint64_t cnt = 0;
      for (int i = 0; i < (int)size(f); ++i)
        if (i % n == as % n) cnt += a[i];
      report(as, n, ("A"s + (cnt > 100 ? "s^"s + to_string(cnt) : string(cnt, 's')) + '!').c_str());
    }
  }

  return 0;
}
