#include <cstdio>
#include <algorithm>

const int kN = 101;
int n, m;
char in[kN * 4];
int ans[kN];

int main() {
  while (scanf("%d %d\n", &n, &m), n != 0 or m != 0) {
    for (int i = 0; i < n; ++i) ans[i] = i;
    for (int i = 0; i < m; ++i) {
      fgets(in, kN * 4, stdin);
      for (int j = 0; j < n; ++j)
        if (in[j * 4] == '+')
          std::swap(ans[j], ans[j + 1]), ++j;
    }
    for (int i = 0; i < n; ++i)
      printf("%d%c", ans[i] + 1, " \n"[i + 1 == n]);
  }
  return 0;
}
