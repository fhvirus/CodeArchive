#include <cstdio>
#include <algorithm>
#include <utility>

int M, N, B;
char g[9][10];

const int di[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dj[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool ok(int i, int j) { return 0 <= i and i < M and 0 <= j and j < N; }

// MINE <= NUM <= MINE + WHAT
enum SLOT { NUM = 0, EMPTY, MINE, WHAT, SIZE };
int a[9][9][SIZE];

bool change_neighbor(int i, int j, SLOT from, SLOT to) {
  auto b = a[i][j];
  for (SLOT k : {EMPTY, MINE, WHAT})
    b[k] += (to == k) - (from == k);
  return b[MINE] <= b[NUM] and b[NUM] <= b[MINE] + b[WHAT];
}

int tot_id, tot_what, tot_mine, tot_arbitrary;
std::pair<int, int> to_fill[9 * 9];

int C[90][90];

int sou(int id);

int test(int id, int i, int j, SLOT to) {
  int ans = 0;
  bool can = true;
  for (int d = 0; d < 8; ++d) {
    int ni = i + di[d], nj = j + dj[d];
    if (ok(ni, nj) and g[ni][nj] != '_')
      can &= change_neighbor(ni, nj, WHAT, to);
  }
  if (can) {
    tot_what -= 1;
    tot_mine += (to == MINE);
    ans += sou(id + 1);
    tot_what += 1;
    tot_mine -= (to == MINE);
  }
  for (int d = 0; d < 8; ++d) {
    int ni = i + di[d], nj = j + dj[d];
    if (ok(ni, nj) and g[ni][nj] != '_')
      change_neighbor(ni, nj, to, WHAT);
  }
  return ans;
}

int sou(int id) {
  if (id == tot_id) return C[tot_what][B - tot_mine];
  auto [i, j] = to_fill[id];

  int ans = 0;
  if (tot_mine + 1 <= B) ans += test(id, i, j, MINE);
  if (B <= tot_what - 1 + tot_mine) ans += test(id, i, j, EMPTY);

  return ans;
}

int main() {
  C[0][0] = 1;
  for (int i = 1; i < 90; ++i) {
    for (int j = 0; j <= i; ++j) {
      C[i][j] = C[i - 1][j];
      if (j > 0) C[i][j] += C[i - 1][j - 1];
      C[i][j] = std::min(C[i][j], 1'000'000'000);
    }
  }

  int T;
  scanf("%d", &T);

  while (T --> 0) {
    scanf("%d%d%d", &M, &N, &B);
    for (int i = 0; i < M; ++i)
      scanf("%s", g[i]);

    tot_id = tot_arbitrary = 0;
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        auto b = a[i][j];
        std::fill(b, b + SIZE, 0);
        b[NUM] = (g[i][j] == '_' ? -1 : g[i][j] - '0');
        for (int d = 0; d < 8; ++d) {
          int ni = i + di[d], nj = j + dj[d];
          if (ok(ni, nj))
            b[ g[ni][nj] == '_' ? WHAT : EMPTY ] += 1;
        }
        if (g[i][j] == '_') {
          bool arb = true;
          for (int d = 0; d < 8; ++d) {
            int ni = i + di[d], nj = j + dj[d];
            if (ok(ni, nj)) arb &= (g[ni][nj] == '_');
          }
          if (arb) tot_arbitrary += 1;
          else to_fill[tot_id++] = std::make_pair(i, j);
        }
      }
    }
    tot_what = tot_id + tot_arbitrary, tot_mine = 0;

    int ans = sou(0);
    printf("%d\n", ans);
  }
}
