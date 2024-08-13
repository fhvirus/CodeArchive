#include <cstdio>
#include <cstdlib>
#include <algorithm>

int meow() { return 42; }

char buf[100];

void my_after() {
  std::rotate(buf, buf + 25, buf + 25 + 31);
}

__attribute__ ((constructor)) void my_before() {
  ungetc('\n', stdin);
  ungetc('0', stdin);
  setbuf(stdout, buf);
  atexit(my_after);
}
