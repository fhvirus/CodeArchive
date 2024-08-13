#include <cstdio>
#include <cctype>
#include <cstring>

const int kN = 200002;

int ch[kN][27];
int tot, mode;
char s[kN], c;
bool has;

void dfs(int u, int i) {
  if (ch[u][26] == 0b1111) puts(s), has = true;
  for (int c = 0; c < 26; ++c) if (ch[u][c] != 0) {
    s[i] = char('a' + c);
    dfs(ch[u][c], i + 1);
  }
  s[i] = 0;
}

int main() {
  mode = 0b0001;
  while (fgets(s, kN, stdin)) {
    int n = (int) strlen(s), u = 0;
    for (int i = 0; i < n; ++i) {
      if (not isalpha(s[i])) {
        if (u != 0) ch[u][26] |= (mode << ((ch[u][26] & mode) != 0));
        u = 0;
      } else {
        s[i] = (char) tolower(s[i]);
        if (ch[u][s[i] - 'a'] == 0) {
          ch[u][s[i] - 'a'] = ++tot;
          memset(ch[tot], 0, sizeof(ch[tot]));
        }
        u = ch[u][s[i] - 'a'];
      }
    }
    mode ^= 0b0101;
    if (mode == 1) {
      memset(s, 0, n);
      has = false;
      dfs(0, 0);
      if (!has) puts("<NONE>");
      puts("");
      tot = 0;
      memset(ch[0], 0, sizeof(ch[tot]));
    }
  }
}
