#include "lib1416.h"

int main() {
  for (int n = Initialize(), t = 2, nt; n > 0; t = nt)
    n -= t + (nt = Take_Stone(t <= n ? t : n));
  return 0;
}
