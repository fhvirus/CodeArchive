#include "lib1542.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  bool type = Initialize();
  vector<int> val(1, type ? INT_MIN : INT_MAX);

  const auto upd = [&](int a) {
    GoBackward(), type = not type;
    auto &v = val.back();
    v = (type ? max(v, a) : min(v, a));
  };

  while (true) {
    while (size(val) > 1) {
      int a = val.back(), b = end(val)[-2];
      if (type ? (a <= b) : (a >= b)) break;
      val.pop_back(); upd(a);
    }
    int res, op;
    res = Ask(&op);
    if (op == 1) {
      val.push_back(type ? INT_MAX : INT_MIN);
      type = not type;
    } else {
      if (op == 2) res = val.back();
      val.pop_back();
      if (empty(val)) { Report(res); exit(0); }
      upd(res);
    }
  }

  return 0;
}
