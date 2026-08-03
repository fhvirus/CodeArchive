#include "lib1341.h"
#include <algorithm>
using namespace std;

int main() {
  int n, x, y;
	Init(&n, &x, &y);
  const auto query = [&](int i, int j) {
    return 1 <= min(i, j) and max(i, j) <= n and Examine(i, j); };

  for (int t : {0, 1, 2})
    for (int l = (1 << __lg(n - x + 1)); l; l /= 2)
      if (query(x + l, y)) x += l;
  for (int t : {0, 1, 2})
    for (int l = (1 << __lg(n - y + 1)); l; l /= 2)
      if (query(x, y + l)) y += l;

  for (int l = (1 << __lg(min(x, y))); l; l /= 2)
    if (query(x - l, y - l)) x -= l, y -= l;

  int len = 0;
  for (int l = (1 << __lg(n - max(x, y) + 1)); l; l /= 2)
    if (query(x + len + l, y + len + l)) len += l;

	Solution(x + len / 2, y + len / 2);
}
