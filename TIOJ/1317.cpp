#include <cstdio>
#include <algorithm>
using namespace std;

const int kN = 2000;
const int kM = kN * kN;
int to[kM], sz[kM], cnt[kM + 1], ord[kM], stk[kM];
char s[kN + 1];

int dfs(int u, bool take) {
  int top = 0;
  stk[top++] = u;
  for (; to[u] != -1 and sz[to[u]] == 0; u = to[u]) {
    sz[u] = -1;
    stk[top++] = to[u];
  }
  u = stk[--top];
  if (to[u] == -1) sz[u] = 1;
  else if (sz[to[u]] == -1) {
    int len = 1;
    for (int v = to[u]; v != u; v = to[v]) len += 1;
    for (int v = to[u]; v != u; v = to[v]) sz[v] = len;
    sz[u] = len;
  } else sz[u] = (take ? sz[to[u]] : 0) + 1;
  while (top > 0) {
    u = stk[--top];
    if (sz[u] == -1)
      sz[u] = sz[to[u]] + 1;
  }
  return sz[u];
}

int main() {
  int n;
  scanf("%d", &n);
  int m = n * n;

  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    for (int j = 0; j < n; ++j) {
      int ni = i + (s[j] == 'd') - (s[j] == 'u');
      int nj = j + (s[j] == 'r') - (s[j] == 'l');
      to[i * n + j] = (0 <= ni and ni < n and 0 <= nj and nj < n) ?
        ni * n + nj : -1;
    }
  }

  int max_sz = 0;
  for (int i = 0; i < m; ++i) if (sz[i] == 0)
    max_sz = max(max_sz, dfs(i, true));
  for (int i = 0; i < m; ++i) cnt[sz[i]] += 1;
  for (int i = max_sz; i > 0; --i) cnt[i - 1] += cnt[i];
  for (int i = 0; i < m; ++i) ord[--cnt[sz[i]]] = i;

  fill(sz, sz + m, 0);
  fill(cnt, cnt + m, 0);
  max_sz = 0;
  for (int i = 0; i < m; ++i) if (sz[ord[i]] == 0) {
    int u = ord[i];
    max_sz = max(max_sz, dfs(u, false));
    cnt[sz[u]] += 1;
  }

  int ans = 0, turn = 1;
  for (int i = max_sz; i > 0; --i) {
    ans += i * ((cnt[i] + turn) / 2);
    turn ^= cnt[i] % 2;
  }
  printf("%d\n", ans);

  return 0;
}
