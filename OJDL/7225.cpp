#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <map>

struct Interacter {
  std::map<int, int> mp;
  int get() {
    int a;
    scanf("%d", &a);
    return a;
  }
  int query(int pos) {
    if (mp.count(pos)) return mp[pos];
    printf("? %d\n", pos);
    fflush(stdout);
    return mp[pos] = get();
  }
  void guess(int val) {
    printf("! %d\n", val);
    fflush(stdout);
    exit(0);
  }
};

int main() {
  Interacter owo;
  int N = owo.get();
  int x = owo.get();

  if (N == 1) owo.guess(owo.query(1));

  // peak: maximum i such that i == N or a[i] > a[i + 1]
  int peak = 1;
  for (int l = (1 << 16); l > 0; l >>= 1)
    if (peak + l <= N and owo.query(peak + l - 1) <= owo.query(peak + l ))
      peak += l;

  int ans = 0;
  for (int i = 0, l = (1 << 16); l > 0; l >>= 1)
    if (i + l <= peak and owo.query(i + l) <= x)
      ans = std::max(ans, owo.query(i += l));
  for (int i = N + 1, l = (1 << 16); l > 0; l >>= 1)
    if (i - l > peak and owo.query(i - l) <= x)
      ans = std::max(ans, owo.query(i -= l));
  owo.guess(ans);
}
