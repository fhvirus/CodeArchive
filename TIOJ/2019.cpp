#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int kN = 1000001;
int T, N, M;
char A[kN], B[kN];
bool vis[kN];
int pos[kN], pre[kN][3], ans[kN];

inline int get(char a) { return 1 - (a == 'S') + (a == 'P'); }

int main() {
  scanf("%d%s%s", &T, A, B);
  N = (int) strlen(A), M = (int) strlen(B);

  bool flip = false;
  if (N > M) std::swap(N, M), std::swap(A, B), flip = true;

  for (int i = 0; i < N; ++i) {
    if (vis[i]) continue;
    std::vector<int> gb;
    int siz = 0;
    for (int h = i, j = i; ;) {
      gb.push_back(j);
      pos[j] = siz;
      siz += 1;
      pre[siz][0] = pre[siz - 1][0];
      pre[siz][1] = pre[siz - 1][1];
      pre[siz][2] = pre[siz - 1][2];
      pre[siz][get(B[j])] += 1;
      j = j + N + (j + N >= M ? -M : 0);
      if (j == h) break;
    }
    for (int j : gb) {
      int k = j % N, u = get(A[k]);
      if (vis[k]) continue;
      vis[k] = true;
      int t = (T - k + N - 1) / N;
      int cyc = t / siz, left = t - cyc * siz;
      ans[0] += pre[siz][(u + 0) % 3] * cyc;
      ans[1] += pre[siz][(u + 1) % 3] * cyc;
      ans[2] += pre[siz][(u + 2) % 3] * cyc;
      int head = pos[k], tail = pos[k] + left;
      if (tail >= siz) {
        ans[0] += pre[siz][(u + 0) % 3] - pre[head][(u + 0) % 3] + pre[tail - siz][(u + 0) % 3];
        ans[1] += pre[siz][(u + 1) % 3] - pre[head][(u + 1) % 3] + pre[tail - siz][(u + 1) % 3];
        ans[2] += pre[siz][(u + 2) % 3] - pre[head][(u + 2) % 3] + pre[tail - siz][(u + 2) % 3];
      } else {
        ans[0] += pre[tail][(u + 0) % 3] - pre[head][(u + 0) % 3];
        ans[1] += pre[tail][(u + 1) % 3] - pre[head][(u + 1) % 3];
        ans[2] += pre[tail][(u + 2) % 3] - pre[head][(u + 2) % 3];
      }
    }
  }

  printf("%d %d %d\n", ans[2 - flip], ans[1 + flip], ans[0]);
}
