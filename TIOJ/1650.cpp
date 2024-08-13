// keyword: Lychrel number
#include <cstdio>

const int kN = 5050;
const int kT = 5000;
int n, len, ans;
int a[kN];

int main() {
  scanf("%d", &n);

  for (len = 0; n; ++len, n /= 10)
    a[len] = n % 10;

  for (ans = 0; ans <= kT; ++ans) {
    bool is = true;
    for (int i = 0, j = len - 1, t; i <= j; ++i, --j) {
      is &= (a[i] == a[j]);
      t = a[i] + a[j];
      a[i] = a[j] = t;
    }
    if (is) break;
    for (int i = 0; i < len; ++i) if (a[i] >= 10) {
      a[i] -= 10;
      a[i + 1] += 1;
    }
    if (a[len] > 0) len += 1;
  }

  if (ans > kT) puts("no");
  else printf("%d\n", ans);

  return 0;
}
