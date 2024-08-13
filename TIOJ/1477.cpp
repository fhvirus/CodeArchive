#include <cstdio>
#include <cstdint>

const uint64_t kB = 10'000'000'000'000'000ul;
const int kN = 2577 / 16 + 1;
uint64_t a[kN], b[kN], ans[kN];
int len_a, len_b, len_ans;

void mult(int v, uint64_t a[], int &len) {
  for (int i = 0; i < len; ++i) a[i] *= v;
  for (int i = 0; i < len; ++i) if (a[i] >= kB) {
    a[i + 1] += a[i] / kB;
    a[i] %= kB;
    if (i + 1 == len) len += 1;
  }
}

void add(uint64_t a[], int &len_a, uint64_t b[], int &len_b) {
  for (int i = 0; i < len_b; ++i) a[i] += b[i];
  if (len_b > len_a) len_a = len_b;
  for (int i = 0; i < len_a; ++i) if (a[i] >= kB) {
    a[i + 1] += 1;
    a[i] -= kB;
    if (i + 1 == len_a) len_a += 1;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  a[0] = 1, len_a = 1, len_ans = 0;
  for (int i = 1; i <= n; ++i) {
    mult(n + 1 - i, a, len_a);
    len_b = len_a;
    for (int j = 0; j <= len_a; ++j)
      b[j] = a[j];
    mult(i, b, len_b);
    add(ans, len_ans, b, len_b);
  }

  printf("%lu", ans[len_ans - 1]);
  for (int i = len_ans - 2; i >= 0; --i)
    printf("%016lu", ans[i]);
  puts("");

  return 0;
}
