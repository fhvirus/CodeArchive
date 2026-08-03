#include "lib1278.h"

char get(int v) {
  if (v < 0xa) return char('0' + v);
  return char('a' + v - 0xa);
}

char s[0x4000 + 1];
int len;

int main() {
  Initialize();

  s[0] = '1';
  len = 1;
  while (Query(s, len) == 0) s[len++] = '0';
  if (len == 1) Answer("0", 1);

  len -= 1;
  for (int i = 0; i < len; ++i) {
    int d = 0x10;
    for (int l = (1 << 3); l; l /= 2) {
      s[i] = get(d - l);
      if (Query(s, len) == 1)
        d -= l;
    }
    s[i] = get(d - 1);
  }

  Answer(s, len);
}
