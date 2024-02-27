#include <cstdio>
#include <algorithm>
#include <vector>

const int kN = 101;
const int kM = 24 * 60;

std::vector<std::tuple<int, int, int>> line[kN];
int dist[kM][kN];

int main() {
  int N, M;
  while (scanf("%d%d", &N, &M), N != 0 or M != 0) {
    for (int i = 1; i <= N; ++i) line[i].clear();
    for (int A, B, P, T, i = 0; i < M; ++i) {
      scanf("%d%d%d%d", &A, &B, &P, &T);
      line[A].emplace_back(B, P, T);
    }

    int Nb, Ne, st, et, HH, MM;
    scanf("%d%d", &Nb, &Ne);
    scanf("%d:%d", &HH, &MM); st = HH * 60 + MM;
    scanf("%d:%d", &HH, &MM); et = HH * 60 + MM;

    for (int i = st; i <= et; ++i)
      for (int j = 1; j <= N; ++j)
        dist[i][j] = kM + 1;

    dist[st][Nb] = 0;
    for (int t = st; t < et; ++t) {
      for (int u = 1; u <= N; ++u) {
        if (dist[t][u] > kM) continue;
        dist[t + 1][u] = std::min(dist[t + 1][u], dist[t][u] + 1);
        for (auto [v, P, T] : line[u]) {
          if (t + T > et or t % P != 0) continue;
          dist[t + T][v] = std::min(dist[t + T][v], dist[t][u]);
        }
      }
    }

    if (dist[et][Ne] > kM) puts("No way");
    else printf("%d\n", dist[et][Ne]);
  }
  return 0;
}
