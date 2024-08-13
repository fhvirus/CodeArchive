#include <cstdio>
#include <bitset>

const int kN = 500;
int T, n, m;
bool adj[kN][kN];
int f[kN * 2];

int find(int u) { return f[u] == u ? u : f[u] = find(f[u]); }

void solve() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      adj[i][j] = false;
  for (int i = 0; i < 2 * n; ++i) f[i] = i;
  for (int a, b, i = 0; i < m; ++i) {
    scanf("%d %d", &a, &b);
    adj[a][b] = true;
    a = find(a);
    b = find(b + n);
    f[b] = a;
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (find(i) == find(j + n) and not adj[i][j])
        return puts("No"), (void) 0;
  puts("Yes");
}

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    printf("Case #%d: ", t);
    solve();
  }
  return 0;
}
