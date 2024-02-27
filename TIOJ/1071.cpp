#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>

const int kN = 55;
const int kL = 55;
const int kM = kN * kL;

int n;
char S[kL], T[kN][kL];

const int IS_END = 26;
int nd[kM][27], tot;
void build_trie() {
  tot = 1;
  std::fill(nd[0], nd[0] + 27, 0);
  for (int i = 0; i < n; ++i) {
    int u = 0;
    for (int j = 0, len = (int) strlen(T[i]); j < len; ++j) {
      int &v = nd[u][T[i][j] - 'a'];
      if (v == 0) {
        std::fill(nd[tot], nd[tot] + 27, 0);
        v = tot++;
      }
      u = v;
    }
    nd[u][IS_END] = 1;
  }
}

std::vector<int> clear_to[kL];
std::pair<int, int> q[kM * kL];
int vis[kM][kL], vis_id, qh, qt;
int dp[kL];

void push(int u, int i) {
  if (vis[u][i] == vis_id) return;
  vis[u][i] = vis_id;
  q[qt++] = std::make_pair(u, i);
}

int main() {
  while (scanf("%d", &n), n != 0) {
    scanf("%s", S);
    for (int i = 0; i < n; ++i)
      scanf("%s", T[i]);

    int m = (int) strlen(S);
    build_trie();
    for (int i = 0; i < m; ++i)
      clear_to[i].clear();

    for (int len = 1; len <= m; ++len) {
      for (int l = 0, r = len - 1; r < m; ++l, ++r) {
        qh = 0, qt = 1, vis_id += 1;
        q[0] = std::make_pair(0, l);
        while (qh < qt) {
          auto [u, i] = q[qh++];
          if (nd[u][IS_END] == 1 and i == r + 1) {
            clear_to[l].push_back(r);
            break;
          }
          if (i == r + 1) continue;
          int v = nd[u][S[i] - 'a'];
          if (v != 0) push(v, i + 1);
          for (int j : clear_to[i]) {
            if (j > r) break;
            push(u, j + 1);
          }
        }
      }
    }

    std::fill(dp, dp + m + 1, m);
    dp[0] = 0;
    for (int i = 0; i < m; ++i) {
      dp[i + 1] = std::min(dp[i + 1], dp[i] + 1);
      for (int j : clear_to[i])
        dp[j + 1] = std::min(dp[j + 1], dp[i]);
    }

    printf("%d\n", dp[m]);
  }
}
