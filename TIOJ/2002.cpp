#include <cstdio>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

void R(int &x) {
  int c;
  for (x = 0; ((c = getchar_unlocked()) < '0'); ) if (c == EOF) return;
  for (; c >= '0'; x = x * 10 + (c ^ '0'), c = getchar_unlocked());
}

const int kN = 200002;
const int kK = 100001;

int N, M, sp[kN], qs[kK][2];
long int p_q, p_s;

int main() {

  R(N), R(M);

  p_q = ftell(stdin);
  for (int i = 0, a, b; i < M; ++i) R(a), R(b);
  p_s = ftell(stdin);

  for (int qs_l = 0; qs_l < M; qs_l += kK) {
    int qs_r = min(qs_l + kK, M);

    fseek(stdin, p_q, SEEK_SET);
    for (int i = 0; qs_l + i < qs_r; ++i) {
      R(qs[i][0]), R(qs[i][1]);
      qs[i][0] -= 1;
      qs[i][0] |= (31 - __builtin_clz(qs[i][1] - qs[i][0])) << 20;
    }
    p_q = ftell(stdin);

    fseek(stdin, p_s, SEEK_SET);
    for (int i = 0; i < N; ++i) R(sp[i]);

    for (int lg = 0, len = 1; len < N; lg += 1, len <<= 1) {
      for (int i = 0; qs_l + i < qs_r; ++i) {
        int &l = qs[i][0], &r = qs[i][1];
        if (l != -1 and (l >> 20) == lg) {
          l = l & ((1 << 20) - 1);
          r = max(sp[l], sp[r - len]);
          l = -1;
        }
      }
      if (len * 2 < N) {
        for (int i = 0; i + len * 2 <= N; ++i)
          sp[i] = max(sp[i], sp[i + len]);
      }
    }

    for (int i = 0; qs_l + i < qs_r; ++i)
      printf("%d\n", qs[i][1]);
  }

  return 0;
}
