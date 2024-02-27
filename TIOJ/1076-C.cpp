#include <cstdio>
#include <cstring>
#include <algorithm>
#include <numeric>

const int kN = 1000;
const int kL = 44;

int N, M;
char dict[kN][kL];
int dict_len[kN];

char buf[kL];
int cand[kN], cand_num;

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%s", dict[i]);
    dict_len[i] = (int) strlen(dict[i]);
  }

  scanf("%d", &M);
  for (int i = 1; i <= M; ++i) {
    scanf(" %[^\n]", buf);
    printf("Query %d: %s, ", i, buf);

    std::iota(cand, cand + N, 0);
    cand_num = N;
    for (int l = 0, r, len = (int) strlen(buf); l < len; l = r + 1) {
      auto p = strchr(buf + l, ' ');
      r = (p == NULL ? len : (int) (p - buf));

      char *pat = buf + l + (buf[l] == '*');
      int pat_len = (r - l) - (buf[r - 1] == '*') - (buf[l] == '*');

      if (buf[l] == '*' and buf[r - 1] == '*') {
        pat[pat_len] = '\0';
        for (int j = 0, k = std::exchange(cand_num, 0); j < k; ++j) {
          if (strstr(dict[cand[j]], pat) != NULL)
            cand[cand_num++] = cand[j];
        }
      } else if (buf[l] == '*') {
        for (int j = 0, k = std::exchange(cand_num, 0); j < k; ++j)
          if (strncmp(dict[cand[j]] + (dict_len[cand[j]] - pat_len), pat, pat_len) == 0)
            cand[cand_num++] = cand[j];
      } else {
        for (int j = 0, k = std::exchange(cand_num, 0); j < k; ++j)
          if (strncmp(dict[cand[j]], pat, pat_len) == 0)
            cand[cand_num++] = cand[j];
      }
    }

    printf("%d item(s) is found.\n", cand_num);
    for (int i = 0; i < cand_num; ++i)
      puts(dict[cand[i]]);
    puts("");
  }

  return 0;
}
