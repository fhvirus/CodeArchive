#ifdef OWO
#include <cstdio>
namespace UWU {
  int n, arr[100];
}
int Initialize() {
  scanf("%d", &UWU::n);
  for (int i = 1; i < UWU::n; ++i)
    scanf("%d", &UWU::arr[i]);
  return UWU::n;
}
int Ask(int i, int j) {
  printf("Ask %d %d = %d\n", i, j, UWU::arr[i] >> (j - 1) & 1);
  return UWU::arr[i] >> j & 1;
}
void Answer(int v) {
  printf("Answer %d\n", v);
}
#else
#include "lib1359.h"
#endif

int main() {
  const int kN = 100;
  int cand_val[kN], cand_pos[kN], m;

  int n = Initialize();

  m = n - 1;
  for (int i = 0; i < n - 1; ++i) cand_val[i] = 0;
  for (int i = 0; i < n - 1; ++i) cand_pos[i] = i + 1;

  int ask_bit = 0, ans = 0;
  while (m > 0) {
    int count_cand = 0;
    for (int i = cand_val[0]; i < n; i += (1 << ask_bit))
      count_cand += (i >> ask_bit & 1);

    int count_real = 0;
    for (int i = 0; i < m; ++i) {
      int t = Ask(cand_pos[i], ask_bit + 1);
      cand_val[i] |= (t << ask_bit);
      count_real += t;
    }

    ans |= ((count_cand != count_real) << ask_bit);

    int t = 0;
    for (int i = 0; i < m; ++i) {
      if ((cand_val[i] >> ask_bit & 1) xor (count_cand != count_real))
        continue;
      cand_val[t] = cand_val[i];
      cand_pos[t] = cand_pos[i];
      t += 1;
    }
    m = t;
    ask_bit += 1;
  }

  Answer(ans);

  return 0;
}
