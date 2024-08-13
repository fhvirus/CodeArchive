#include "lib1455.h"
#define get_id(i) (s[i] == 'B' ? 2 : (s[i] == 'G'))

int main() {
  TakeCake();

  int n;
  scanf("%d", &n);

  char s[1000];
  scanf("%s", s);

  int cnt[3] = {0, 0, 0};
  for (int i = 0; i < n; ++i)
    cnt[get_id(i)] += 1;

  int stk[1000], top = 0;
  How_Many_Cut(n - 3);
  int st = -1;
  for (int i = 0; i < n; ++i) {
    stk[top++] = i;
    while (top >= 3 and s[stk[top - 1]] != s[stk[top - 2]] and
        s[stk[top - 1]] != s[stk[top - 3]] and
        s[stk[top - 2]] != s[stk[top - 3]]) {
      if (cnt[get_id(stk[top - 2])] == 1) {
        if (st == -1) st = top - 2;
        break;
      }
      if (not (stk[top - 3] == 0 and stk[top - 1] == n - 1))
        Cut(stk[top - 3] + 1, stk[top - 1] + 1);
      cnt[get_id(stk[top - 2])] -= 1;
      stk[top - 2] = stk[top - 1];
      top -= 1;
    }
  }
  for (int i = 3, j = (st + 2) % top; i < top;
      ++i, j = (j + 1 == top ? 0 : j + 1))
    Cut(stk[st] + 1, stk[j] + 1);

  Finish();

  return 0;
}
