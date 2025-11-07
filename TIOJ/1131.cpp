#include <bits/stdc++.h>
using namespace std;

const int DN[53] = { 1, 1, 2, 3, 4, 6, 9, 13, 19, 28, 41, 60, 88, 129, 189, 277, 406, 595, 872, 1278, 1873, 2745, 4023, 5896, 8641, 12664, 18560, 27201, 39865, 58425, 85626, 125491, 183916, 269542, 395033, 578949, 848491, 1243524, 1822473, 2670964, 3914488, 5736961, 8407925, 12322413, 18059374, 26467299, 38789712, 56849086, 83316385, 122106097, 178955183, 262271568, 384377665 };
int a[53], pre[53];

int solve(int i, int price, int min_cost) {
  if (price == 0) return 0;
  if (i == 0) return INT_MAX / 2;
  if (pre[i - 1] >= price)
    min_cost = min(min_cost, solve(i - 1, price, min_cost));
  if (a[i] < min_cost and DN[i] <= price)
    min_cost = min(min_cost, solve(i - 1, price - DN[i], min_cost - a[i]) + a[i]);
  return min_cost;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  partial_sum(DN, DN + 53, pre);

  int N;
  while (cin >> N) {
    int len = 1;
    for (; len < 53 and DN[len] <= N; ++len) cin >> a[len];
    len -= 1;

    cout << solve(len, N, N) << '\n';
  }

  return 0;
}
