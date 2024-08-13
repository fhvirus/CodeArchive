#include <cstdio>
#include <cstring>
#include <algorithm>

const int kN = 1010;
int a;
char b[kN], c[kN];
bool cmp(int n, int len) { // return b >= c
  if (n != len) return n > len;
  for (int i = n - 1; i >= 0; --i)
    if (b[i] != c[i]) return b[i] > c[i];
  return true;
}

int main() {

  while (scanf("%d\n%s", &a, b) != EOF) {
    int n = (int) strlen(b);
    std::reverse(b, b + n);
    for (int i = 0; i < n; ++i) b[i] -= '0';

    int ans = 0, len = 1;
    std::fill(c, c + n + 1, 0);
    c[0] = 1;
    while (cmp(n, len)) {
      for (int i = 0; i < len; ++i)
        c[i] *= a;
      for (int i = 0; i < len; ++i) if (c[i] >= 10) {
        c[i + 1] += c[i] / 10;
        c[i] = c[i] % 10;
        if (i == len - 1) len += 1;
      }
      ++ans;
    }
    printf("%d\n", ans - 1);
  }

  return 0;
}
