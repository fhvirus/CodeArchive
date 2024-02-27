#include <cstdio>

int T, M, N;
char g[20][35];

int counter, last_update, tot_mine;

bool ok(int i, int j)
{ return 0 <= i and i < M and 0 <= j and j < N; }

const int di[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dj[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
void flip(int i, int j) {
  last_update = counter;
  int mine = 0;
  for (int d = 0; d < 8; ++d) {
    int ni = i + di[d], nj = j + dj[d];
    mine += (ok(ni, nj) and (g[ni][nj] == '*' or g[ni][nj] == 'F'));
  }
  g[i][j] = char('0' + mine);
}
void flag(int i, int j) {
  last_update = counter;
  g[i][j] = 'F';
}

enum Mark { E = 0, X, Y };
Mark mark[20][35];

bool contra(int i, int j) {
  if ('0' > g[i][j] or g[i][j] > '8') return false;
  int Q = g[i][j] - '0';
  int A = 0, C = 0;
  for (int d = 0; d < 8; ++d) {
    int ni = i + di[d], nj = j + dj[d];
    if (!ok(ni, nj)) continue;
    if (g[ni][nj] == 'F') A += 1;
    if ((g[ni][nj] == '_' or g[ni][nj] == '*') and mark[ni][nj] != Y) C += 1;
  }
  return A + C < Q;
}

void rule123(int i, int j) {
  if ('0' > g[i][j] or g[i][j] > '8') return;
  int num = g[i][j] - '0';
  int neighbor = 0, flagged = 0, flipped = 0;
  for (int d = 0; d < 8; ++d) {
    int ni = i + di[d], nj = j + dj[d];
    if (!ok(ni, nj)) continue;
    neighbor += 1;
    if (g[ni][nj] == 'F') flagged += 1;
    if ('0' <= g[ni][nj] and g[ni][nj] <= '8') flipped += 1;
  }
  int unknown = neighbor - flagged - flipped;
  if (flagged == num) { // rule 2
    for (int d = 0; d < 8; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (ok(ni, nj) and (g[ni][nj] == '_' or g[ni][nj] == '*'))
        flip(ni, nj);
    }
  } else if (unknown + flagged == num) { // rule 1
    for (int d = 0; d < 8; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (ok(ni, nj) and (g[ni][nj] == '_' or g[ni][nj] == '*'))
        flag(ni, nj);
    }
  } else if (flagged + 1 == num) { // rule 3
    for (int d = 0; d < 8; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (!ok(ni, nj) or ('0' <= g[ni][nj] and g[ni][nj] <= '8') or g[ni][nj] == 'F') continue;
      mark[ni][nj] = Y;
    }
    for (int d = 0; d < 8; ++d) {
      bool found = false;
      int ni = i + di[d], nj = j + dj[d];
      if (!ok(ni, nj) or ('0' <= g[ni][nj] and g[ni][nj] <= '8') or g[ni][nj] == 'F') continue;
      mark[ni][nj] = X;
      char tmp = g[ni][nj];
      g[ni][nj] = 'F';
      for (int ti = ni - 2; ti <= ni + 2 and !found; ++ti) {
        for (int tj = nj - 2; tj <= nj + 2 and !found; ++tj) {
          if (!ok(ti, tj) or !contra(ti, tj)) continue;
          flip(ni, nj);
          found = true;
        }
      }
      mark[ni][nj] = found ? E : Y;
      if (!found) g[ni][nj] = tmp;
    }
    for (int d = 0; d < 8; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (!ok(ni, nj)) continue;
      mark[ni][nj] = E;
    }
  }
}

void rule4() {
  int flagged = 0, flipped = 0;
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      if (g[i][j] == 'F') flagged += 1;
      if ('0' <= g[i][j] and g[i][j] <= '8') flipped += 1;
    }
  }
  int unknown = M * N - flagged - flipped;
  if (flagged == tot_mine) {
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < N; ++j)
        if (g[i][j] == '_' or g[i][j] == '*')
          flip(i, j);
    last_update = -1;
  }
  if (unknown == tot_mine - flagged) {
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < N; ++j)
        if (g[i][j] == '_' or g[i][j] == '*')
          flag(i, j);
    last_update = -1;
  }
}

int main() {

  scanf("%d", &T);

  while (T --> 0) {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; ++i)
      scanf("%s", g[i]);

    tot_mine = 0;
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < N; ++j)
        tot_mine += (g[i][j] == '*');

    for (last_update = -1, counter = 0; ; ++counter) {
      for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
          rule123(i, j);
      rule4();
      if (last_update < counter)
        break;
    }

    for (int i = 0; i < M; ++i)
      puts(g[i]);
  }

  return 0;
}
