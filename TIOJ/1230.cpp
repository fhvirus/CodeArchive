#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <utility>

const int kN = 7, INF = 8e7;
int m, n, a[kN][kN];

const int di[4] = {1, 0, -1, 0};
const int dj[4] = {0, 1, 0, -1};

#define enc(i, j) ((i) * 8 + (j))
#define get_i(a) ((a) / 8)
#define get_j(a) ((a) % 8)
#define has(a, i, j) (((a) >> enc(i, j)) & 1)
#define turn_on(a, i, j) (a |= (1ull << enc(i, j)))

std::pair<uint64_t, int> check(uint64_t vis) {
  static int q[kN * kN];
  uint64_t check_vis = 0;
  int sum = 0, qh = 0, qt = 0;
  turn_on(check_vis, m - 1, n - 1);
  q[qt++] = enc(m - 1, n - 1);
  while (qh < qt) {
    int i = get_i(q[qh]), j = get_j(q[qh]);
    qh += 1;
    sum += a[i][j];
    for (int d = 0; d < 4; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (0 <= ni and ni < m and 0 <= nj and nj < n and !has(vis, ni, nj) and !has(check_vis, ni, nj)) {
        turn_on(check_vis, ni, nj);
        q[qt++] = enc(ni, nj);
      }
    }
  }
  return std::make_pair(check_vis, sum);
}

int dfs(int i, int j, int p, uint64_t vis, uint64_t no, int sum, int best, int tot) {
  auto [can_reach, pos_tot] = check(vis | no);
  if (!has(can_reach, i, j)) return best;
  if (p == 1 and sum + pos_tot <= best) return best;

  turn_on(vis, i, j);
  int tmp = a[i][j];
  sum += a[i][j];
  a[i][j] = 0;

  if (i == m - 1 and j == n - 1) {
    if (p == 0) best = std::max(best, dfs(0, 0, 1, 0, no, sum, best, tot));
    else best = std::max(sum, best);
  } else {
    for (int d = 0; d < 4; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (0 <= ni and ni < m and 0 <= nj and nj < n and !has(vis | no, ni, nj) and has(can_reach, ni, nj))
        best = std::max(best, dfs(ni, nj, p, vis, no, sum, best, tot));
      if (best == tot) break;
    }
  }

  a[i][j] = tmp;
  return best;
}

int main() {
  scanf("%d%d", &m, &n);
  uint64_t no = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      char c;
      scanf(" %c", &c);
      a[i][j] = (c == 'x' ? -1 : c - '0');
      if (c == 'x') turn_on(no, i, j);
    }
  }

  auto [can_reach, tot] = check(no);

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!has(can_reach, i, j))
        a[i][j] = -1, turn_on(no, i, j);
    }
  }

  printf("%d\n", dfs(0, 0, 0, 0, no, 0, 0, tot));

  return 0;
}
