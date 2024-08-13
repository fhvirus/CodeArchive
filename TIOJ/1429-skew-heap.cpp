#include <cstdio>
#include <cstdint>
#include <algorithm>

const int kN = 100001;
int N, M;
int B[kN], C[kN], L[kN];
int64_t sum[kN];
int siz[kN];

int root[kN];
struct Node { int val, lc, rc; };
Node nds[kN];

int merge(int u, int v) {
  if (u == 0 or v == 0) return u | v;
  if (nds[u].val < nds[v].val) std::swap(u, v);
  std::swap(nds[u].lc, nds[u].rc);
  nds[u].rc = merge(nds[u].rc, v);
  return u;
}

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 1; i <= N; ++i) {
    scanf("%d %d %d", &B[i], &C[i], &L[i]);
    sum[i] = C[i];
    siz[i] = 1;
    root[i] = i;
    nds[i].val = C[i];
  }
  int64_t ans = 0;
  for (int i = N; i >= 1; --i) {
    while (sum[i] > M) {
      sum[i] -= nds[root[i]].val;
      siz[i] -= 1;
      root[i] = merge(nds[root[i]].lc, nds[root[i]].rc);
    }
    ans = std::max(ans, (int64_t) L[i] * siz[i]);
    int p = B[i];
    root[p] = merge(root[p], root[i]);
    sum[p] += sum[i];
    siz[p] += siz[i];
  }
  printf("%ld\n", ans);
  return 0;
}
