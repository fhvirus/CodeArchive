#include <cstdio>
#include <cassert>

int main() {
  int N, P;
  scanf("%d %d", &N, &P);
  assert(0 <= N and N <= 1'000);
  assert(0 <= P and P <= 1'000'000'000);

  for (int i = 1; i <= N; ++i)
    printf("%d %d %d\n", i, i, i);
}
