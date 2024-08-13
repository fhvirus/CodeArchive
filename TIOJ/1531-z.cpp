#include <cstdio>
#include <cstring>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int kN = 5000005;
char s[kN];
int z[kN];

int main() {
  int k, n, ans = 0;
  scanf("%d", &k);
  scanf("%s", s);
  n = (int) strlen(s);

  if (k == 1) ans = n;
  else {
    int l = 0, r = 0;
    for (int i = 1; i * k < n; ++i) {
      if (i < r) z[i] = min(r - i, z[i - l]);
      while (i + z[i] < n and s[i + z[i]] == s[z[i]]) ++z[i];
      if (i + z[i] > r) l = i, r = i + z[i];
      if (i + z[i] >= k * i) ans = max(ans, i);
    }
  }

  printf("%d\n", ans);

  return 0;
}
