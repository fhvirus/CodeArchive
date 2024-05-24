#include <cstdio>
#include <algorithm>

const int kU = 1000001;
int num_of_occ[kU];
long long pre[kU];

int main() {

  num_of_occ[1] = 1;
  num_of_occ[2] = 2;
  pre[1] = 1, pre[2] = 3;
  for (int i = 3, j = 2; i < kU; ++i) {
    while (pre[j] < i) ++j;
    num_of_occ[i] = j;
    pre[i] = pre[i - 1] + num_of_occ[i];
  }

  long long n;
  while (scanf("%lld", &n) != EOF and n != 0)
    printf("%d\n", (int) (std::lower_bound(pre, pre + kU, n) - pre));

  return 0;
}
