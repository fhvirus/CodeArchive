#pragma GCC optimize("Ofast")
#include <cstdio>
#include <algorithm>
using namespace std;

int get_int() {
  int res = 0, c;
  do { c = getchar(); } while ('0' > c or c > '9');
  do {
    res = res * 10 + (c - '0');
    c = getchar();
  } while ('0' <= c and c <= '9');
  return res;
}
constexpr int ceil_div(int a, int b) { return (a + b - 1) / b; }

const int kN = 200000, kSQ = 15343, kSS = 19313;
const int kBQ = ceil_div(kN, kSQ), kBS = ceil_div(kN, kSS);
int N, M, a[kSQ], s[kSS], ans[kSQ], qb, sb;
long q_pos[kBQ], s_pos[kBS];

void init_pos() {
  for (int i = 0; i < M; ++i) {
    if (i % kSQ == 0) q_pos[i / kSQ] = ftell(stdin);
    get_int();
    get_int();
  }
  for (int i = 0; i < N; ++i) {
    if (i % kSS == 0) s_pos[i / kSS] = ftell(stdin);
    get_int();
  }
}

int main() {
  N = get_int();
  M = get_int();

  qb = ceil_div(M, kSQ);
  sb = ceil_div(N, kSS);
  init_pos();

  for (int qi = 0; qi < qb; ++qi) {
    int ql = qi * kSQ, qr = min(ql + kSQ, M), qn = qr - ql;
    fill(ans, ans + qn, 0);

    for (int si = 0; si < sb; ++si) {
      int sl = si * kSS, sr = min(sl + kSS, N), sn = sr - sl;

      fseek(stdin, q_pos[qi], SEEK_SET);
      for (int i = 0; i < qn; ++i) {
        int l = min(max(0, get_int() - 1 - sl), sn),
            r = max(min(sn, get_int() - sl), l);
        a[i] = (r << 16 | l);
      }

      fseek(stdin, s_pos[si], SEEK_SET);
      for (int i = 0; i < sn; ++i) s[i] = get_int();

      for (int len = 1; len <= sn; len *= 2) {
        for (int i = 0; i < qn; ++i) {
          int r = (a[i] >> 16), l = (a[i] & 0xffff);
          if ((r - l) & len) {
            ans[i] = max(ans[i], s[l]);
            a[i] += len;
          }
        }
        for (int i = 0; i + len < sn; ++i)
          s[i] = max(s[i], s[i + len]);
      }
    }

    for (int i = 0; i < qn; ++i)
      printf("%d\n", ans[i]);
  }

  return 0;
}
