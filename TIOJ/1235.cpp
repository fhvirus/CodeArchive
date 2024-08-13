// Modified from TIOJ 1025
#include <cstdio>
#include <cstdlib>
#include <cstring>

char in[9][10];
int g[9][9];
int row[9], col[9], box[9];
int nr[9][9], nc[9][9];

int get_id(char c) {
  static const char t[] = "*ROYGBIPLW";
  return (int) (strchr(t, c) - t);
}

void dfs(int r, int c) {
  if (r == -1 and c == -1) {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j)
        if (in[i][j] == '*')
          putchar("*ROYGBIPLW"[g[i][j]]);
      putchar('\n');
    }
    exit(0);
  }

  int can = ((1 << 10) - 2) & (~(row[r] | col[c] | box[r - r%3 + c/3]));
  for (int k = 1; k <= 9; ++k) {
    if ((can >> k & 1) == 0) continue;
    g[r][c] = k;
    row[r] |= (1 << k);
    col[c] |= (1 << k);
    box[r - r%3 + c/3] |= (1 << k);
    dfs(nr[r][c], nc[r][c]);
    g[r][c] = 0;
    row[r] ^= (1 << k);
    col[c] ^= (1 << k);
    box[r - r%3 + c/3] ^= (1 << k);
  }
}

int main() {
  int r = 0, c = 0;
  for (int i = 0; i < 9; ++i) {
    scanf("%s", in[i]);
    for (int j = 0; j < 9; ++j) {
      g[i][j] = get_id(in[i][j]);
      if (g[i][j] != 0) {
        row[i] |= (1 << g[i][j]);
        col[j] |= (1 << g[i][j]);
        box[i - i%3 + j/3] |= (1 << g[i][j]);
      } else {
        nr[r][c] = i;
        nc[r][c] = j;
        r = i;
        c = j;
      }
    }
  }
  nr[r][c] = -1;
  nc[r][c] = -1;

  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j)
      if (g[i][j] == 0)
        dfs(i, j);

  return 0;
}
