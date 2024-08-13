// 我猜 pooh 第一和第二喜歡的 VTuber 是 Ina'nis 和 Subaru！
// 有猜對嗎？
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <cassert>

#define popcnt(x) __builtin_popcountll(x)

int main() {
  int64_t A, B, k;
  scanf("%ld %ld %ld", &A, &B, &k);
  assert(0 <= A and A <= 1'000'000'000'000'000'000l);
  assert(0 <= B and B <= 1'000'000'000'000'000'000l);
  assert(0 <= k and k <= 1'000'000'000'000'000'000l);

  if (popcnt(A) != popcnt(B))
    return puts("No"), 0;

  int cnt = 0;
  for (int i = 0; (A >> i) > 0 or (B >> i) > 0; ++i)
    cnt += abs(popcnt(A >> i) - popcnt(B >> i));

  puts(cnt <= k and cnt % 2 == k % 2 ? "Yes" : "No");
}
