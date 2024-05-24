#include <cstdio>

const int kN = 1000001;
int N, pos[kN];
int stk[kN], par[kN];

int main() {
  scanf("%d", &N);
  for (int a, i = 1; i <= N; ++i) {
    scanf("%d", &a);
    pos[a] = i;
  }

  int t = 1;
  for (int i = 1; i <= N; ++i) {
    int v = pos[i], tt = t;
    while (pos[stk[tt - 1]] >= v) {
      tt -= 1;
      par[stk[tt]] = stk[tt - 1];
    }
    if (tt < t)
      par[stk[tt]] = i;
    t = tt;
    stk[t++] = i;
  }
  while (t > 1) {
    t -= 1;
    par[stk[t]] = stk[t - 1];
  }

  for (int i = 1; i <= N; ++i)
    printf("%d\n", par[i]);

  return 0;
}
