#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <numeric>

const int kN = 1000;
const int kL = 44;

int N, M;
std::string dict[kN];

char buf[kL];
int cand[kN], cand_num;

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%s", buf);
    dict[i] = std::string(buf);
  }

  scanf("%d", &M);
  for (int i = 1; i <= M; ++i) {
    scanf(" %[^\n]", buf);

    std::iota(cand, cand + N, 0);
    cand_num = N;
    for (int l = 0, r, len = (int) strlen(buf); l < len; l = r + 1) {
      auto p = strchr(buf + l, ' ');
      r = (p == NULL ? len : (int) (p - buf));

      std::string pat(buf + l + (buf[l] == '*'), (r - l) - (buf[r - 1] == '*') - (buf[l] == '*'));
      if (buf[l] == '*' and buf[r - 1] == '*') {
        for (int j = 0, k = std::exchange(cand_num, 0); j < k; ++j)
          if (dict[cand[j]].find(pat) != std::string::npos)
            cand[cand_num++] = cand[j];
      } else if (buf[l] == '*') {
        for (int j = 0, k = std::exchange(cand_num, 0); j < k; ++j)
          if (dict[cand[j]].ends_with(pat)) // C++20
            cand[cand_num++] = cand[j];
      } else {
        for (int j = 0, k = std::exchange(cand_num, 0); j < k; ++j)
          if (dict[cand[j]].starts_with(pat))
            cand[cand_num++] = cand[j];
      }
    }

    printf("Query %d: %s, %d item(s) is found.\n", i, buf, cand_num);
    for (int i = 0; i < cand_num; ++i)
      puts(dict[cand[i]].c_str());
    puts("");
  }

  return 0;
}
