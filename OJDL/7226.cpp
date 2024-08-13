#include <cstdio>
#include <cassert>

int main() {
  int N, P;
  scanf("%d %d", &N, &P);
  assert(2 <= N and N <= 200000);
  assert(1 <= P and P <= 1'000'000'000);

  int ans = 0, sum = 0;
  for (int A, i = 0; i < N; ++i) {
    scanf("%d", &A);
    assert(0 <= A and A < P);
    ans += (int) ((long long) A * sum % P);
    if (ans >= P) ans -= P;
    sum += A;
    if (sum >= P) sum -= P;
  }

  printf("%d\n", ans);
}
