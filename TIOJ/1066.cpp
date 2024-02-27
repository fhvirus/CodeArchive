#include <cstdio>
#define min(a, b) (a < b ? a : b)
#define solve(a) do { \
  take = min(p##a + q##a, change / a); \
  ans += take; \
  change -= take * a; \
} while(0)

int main() {
  int n;
  scanf("%d", &n);
  while (n --> 0) {
    int C;
    scanf("%d", &C);

    int p1, p5, p10, p20, p50;
    scanf("%d%d%d%d%d", &p1, &p5, &p10, &p20, &p50);

    int q1, q5, q10, q20, q50;
    scanf("%d%d%d%d%d", &q1, &q5, &q10, &q20, &q50);

    int sum = p1 + 5 * p5 + 10 * p10 + 20 * p20 + 50 * p50;
    int change = sum - C;

    int take, ans = 0;
    solve(50);
    solve(20);
    solve(10);
    solve(5);
    solve(1);

    printf("%d\n", ans);
  }
}
