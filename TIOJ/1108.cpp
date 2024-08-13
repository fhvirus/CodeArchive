#include <cstdio>
#include <cstring>

char pre[55], in[55], post[55], stk[55];
bool in_stk[128];

char ch[128][55];
int cnt[128], tot;

void dfs(char c) {
  for (int i = 0; i < cnt[c]; ++i)
    dfs(ch[c][i]);
  post[tot++] = c;
}

int main() {
  while (scanf("%s%s", pre, in) != EOF) {
    memset(ch, 0, sizeof(ch));
    memset(cnt, 0, sizeof(cnt));
    memset(in_stk, 0, sizeof(in_stk));
    memset(post, 0, sizeof(post));
    tot = 0;

    int n = strlen(pre);
    for (int t = 0, i = 0, j = 0; i < n; ++i) {
      while (not in_stk[in[i]]) {
        stk[++t] = pre[j];
        in_stk[pre[j]] = true;
        j += 1;
        if (t > 1)
          ch[stk[t - 1]][cnt[stk[t - 1]]++] = stk[t];
      }
      while (stk[t] != in[i]) {
        in_stk[stk[t]] = false;
        t -= 1;
      }
    }
    dfs(stk[1]);
    puts(post);
  }
}
