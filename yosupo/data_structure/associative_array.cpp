#include <bits/stdc++.h>
#include <bits/extc++.h>

struct chash {
  const uint64_t C = int64_t(4e18 * acos(0)) | 71;
  int64_t operator()(int64_t x) const { return __builtin_bswap64(x*C); }
};

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin.exceptions(std::cin.failbit);

  int Q;
  std::cin >> Q;

  __gnu_pbds::gp_hash_table<int64_t, int64_t, chash> a({},{},{},{},{1<<16});
  while (Q --> 0) {
    int t;
    int64_t k, v;
    std::cin >> t;
    if (t == 0) {
      std::cin >> k >> v;
      a[k] = v;
    } else {
      std::cin >> k;
      auto it = a.find(k);
      std::cout << (it == a.end() ? 0 : it->second) << '\n';
    }
  }

  return 0;
}
