#include <bits/stdc++.h>
using namespace std;

const int kN = 32;
bitset<64> is_prime("0010100000100000100010100010000010100000100010100010100010101100");
uint64_t adj[kN + 1];

void dfs(int u, int i, int n, int& cnt, uint64_t vis, auto& stk) {
  stk.push_back(u);
  if (i == n) {
    if (is_prime[stk[0] + u]) {
      for (int &v : stk) cout << v << " \n"[v == u];
      cnt += 1;
    }
    stk.pop_back();
    return;
  }
  for (auto to = adj[u] & ~vis; to != 0 and cnt < 3; ) {
    int v = (int) __lg(to & -to);
    if (v > n) break;
    dfs(v, i + 1, n, cnt, vis | (1ul << v), stk);
    to ^= (1ul << v);
  }
  stk.pop_back();
  return;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int i = 1; i <= kN; ++i)
    for (int j = 1; j <= kN; ++j)
      if (i != j and is_prime[i + j])
        adj[i] |= (1ul << j);

  vector<int> stk;
  for (int n, cnt; cin >> n, n != 0; )
    dfs(1, 1, n, cnt = 0, 1ul << 1, stk);

  return 0;
}
