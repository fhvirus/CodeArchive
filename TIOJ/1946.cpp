#include <cstdio>
#include <algorithm>

const int kN = 1000001;

int N, a[kN], deg[kN], left[kN];

int bit[kN];
void add(int p) {
  for (; p <= N; p += p & -p) ++bit[p];
}
int query(int p) {
  int ans = 0;
  for (; p > 0; p -= p & -p) ans += bit[p];
  return ans;
}
int search(int v) {
  int sum = 0, p = 0;
  for (int l = (1 << 19); l > 0; l >>= 1)
    if (p + l <= N and sum + bit[p + l] <= v)
      sum += bit[p += l];
  return p + 1;
}

int main(){
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", a + i);
    a[i] += 1;
  }

  for (int i = 0; i < N; ++i) {
    int cnt = query(a[i]);
    if (i - cnt == 0) left[i] = kN;
    else left[i] = search(cnt + (i - cnt - 1) / 2);
    add(a[i]);
  }

  std::fill(bit, bit + N + 1, 0);
  for (int i = N - 1; i >= 0; --i) {
    int cnt = query(a[i]), right;
    if ((N - i - 1) - cnt == 0) right = kN;
    else right = search(cnt + ((N - i - 1) - cnt - 1) / 2);
    if (a[i] != N) deg[std::min(left[i], right)] += 1;
    add(a[i]);
  }

  deg[N] -= 1;
  printf("%d\n", *std::max_element(deg + 1, deg + N + 1) + 1);
}
