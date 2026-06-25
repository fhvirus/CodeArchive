#include "lib2427.h"

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = Get_Box();
  if (n == 1) { Report(1); return 0; }

  vector<int> id(n);
  iota(begin(id), end(id), 1);
  shuffle(begin(id), end(id), mt19937(std::chrono::system_clock::now().time_since_epoch().count()));

  int lb = -1, rb = -1, pos = n / 2;
  const auto comp = [&](int u, int v) {
    if (lb == -1 and rb == -1) exit(-1);
    if (lb != -1) return Med3(lb, u, v) == u;
    return Med3(u, v, rb) == v;
  };
  while (size(id) > 3) {
    n = int(size(id));
    int m1 = id[n - 1], m2 = id[n - 2];
    if ((lb != -1 or rb != -1) and comp(m2, m1))
      swap(m1, m2);

    vector<vector<int>> buckets(5);
    buckets[1].push_back(m1);
    buckets[3].push_back(m2);
    for (int i = 0; i < n - 2; ++i) {
      int v = Med3(m1, m2, id[i]);
      if (v == m1) buckets[0].push_back(id[i]);
      else if (v == m2) buckets[4].push_back(id[i]);
      else buckets[2].push_back(id[i]);
    }

    for (int i = 0; i < int(size(buckets)); ++i)
      while (i < int(size(buckets)) and empty(buckets[i]))
        buckets.erase(begin(buckets) + i);

    int b = 0;
    while (pos >= int(size(buckets[b]))) {
      pos -= int(size(buckets[b]));
      b += 1;
    }
    if (lb == -1 and b > 0) lb = buckets[b - 1][0];
    if (rb == -1 and b < int(size(buckets)) - 1) rb = buckets[b + 1][0];
    swap(id, buckets[b]);
  }

  ranges::sort(id, comp);
  Report(id[pos]);

  return 0;
}
