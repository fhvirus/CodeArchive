#include <cstdio>
#include <cctype>

//         ref:     `abcdefghijklmnopqrstuvwxyz
const char dot[] = "er  bi z s c gd   lhnf p   ";
const char bar[] = "tw  xa q u y ok    vm  j   ";

int main() {
  char state = '`';
  int eat = 1, last = 0;
  bool end = true;
  const auto go = [&](int v) {
    if (eat > 0) { --eat; last = v & 1; return; }
    int t = v & 1;
    v = (last << 1) | (v >> 1);
    if (v == 0b10) state = dot[state - '`'], end = false;
    if (v == 0b11) state = bar[state - '`'], eat = 1, end = false;
    if (v == 0b00) {
      if (end) {
        putchar(' ');
        eat = 1;
        end = false;
      } else {
        putchar(state);
        state = '`';
        end = true;
      }
    }
    last = t;
  };

  for (int c; isalnum(c = getchar()); ) {
    int v = (isdigit(c) ? c - '0' : c - 'a' + 10);
    go(v / 4); go(v % 4);
  }
  go(0);

  if (state != '`') putchar(state);
  putchar('\n');

  return 0;
}
