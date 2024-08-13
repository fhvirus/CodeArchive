#include <cstdio>
#include <bitset>

const int kN = 500;
int T, n, m;
std::bitset<kN> adj[kN];

void solve() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) adj[i].reset();
  for (int a, b, i = 0; i < m; ++i) {
    scanf("%d %d", &a, &b);
    adj[a].set(b);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      bool diff = (adj[i] ^ adj[j]).any();
      bool inter = (adj[i] & adj[j]).any();
      if (diff and inter) return puts("No"), (void) 0;
    }
  }
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
