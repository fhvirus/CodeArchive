// By https://jasondoucette.com/worldrecords.html#Most
// Answers are always <= 98 when x < 10^9
#include <cstdio>
#include <cstdint>

const int kN = 5050;
const int kT = 100;
const int kD = 18;
const int kL = kN / kD + 1;
uint64_t a[kL], b[kL];

const uint64_t pow10[kD + 1] = {
  1ul,
  10ul,
  100ul,
  1000ul,
  10000ul,
  100000ul,
  1000000ul,
  10000000ul,
  100000000ul,
  1000000000ul,
  10000000000ul,
  100000000000ul,
  1000000000000ul,
  10000000000000ul,
  100000000000000ul,
  1000000000000000ul,
  10000000000000000ul,
  100000000000000000ul,
  1000000000000000000ul
};
uint64_t rev[1000];

inline uint64_t rev_num(uint64_t x) {
  return rev[x / pow10[15]]
    + rev[x % pow10[15] / pow10[12]] * pow10[3]
    + rev[x % pow10[12] / pow10[9]] * pow10[6]
    + rev[x % pow10[9] / pow10[6]] * pow10[9]
    + rev[x % pow10[6] / pow10[3]] * pow10[12]
    + rev[x % pow10[3]] * pow10[15];
}

inline int cnt_trailing_zero(uint64_t x) {
  int r = -1;
  while (x % pow10[++r] == 0);
  return r - 1;
}

int main() {
  for (int i = 0; i < 1000; ++i) rev[i] = (i % 10) * 100 + (i / 10 % 10) * 10 + (i / 100);

  scanf("%lu", &a[0]);

  int ans = 0, len = 1;
  for (; ans <= kT; ++ans) {
    for (int i = 0; i < len; ++i)
      b[i] = rev_num(a[len - 1 - i]);
    int ctz = cnt_trailing_zero(b[0]);
    for (int i = 0; i < len; ++i)
      b[i] = b[i] / pow10[ctz] + b[i + 1] % pow10[ctz] * pow10[kD - ctz];

    bool is = true;
    for (int i = 0; i < len; ++i) is &= (a[i] == b[i]);
    if (is) break;

    for (int i = 0; i < len; ++i) {
      a[i] += b[i];
      if (a[i] >= pow10[kD]) {
        a[i] -= pow10[kD];
        a[i + 1] += 1;
      }
      if (a[len] != 0) len += 1;
    }
  }

  if (ans > kT) puts("no");
  else printf("%d\n", ans);

  return 0;
}
