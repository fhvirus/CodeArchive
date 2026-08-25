// Che Orz
#include <bits/stdc++.h>
using namespace std;

struct Seguki {
  int n;
  vector<int> val;
  Seguki(int _n) : n(_n <= 1 ? 1 : 2 << __lg(_n-1)), val(n*2) {}
  void modify(int p, int v) {
    val[p += n] = v;
    for (p /= 2; p; p /= 2)
      val[p] = max(val[p*2], val[p*2+1]);
  }
  int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) res = max(res, val[l++]);
      if (r & 1) res = max(res, val[--r]);
    }
    return res;
  }
  int get(int i) { return val[i + n]; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K, Q;
  cin >> N >> K >> Q;

  const int B = (N + K - 1) / K;

  Seguki all(N), block(B);
  vector<priority_queue<pair<int, int>>> vs(B);
  for (int a, i = 0; i < N; ++i) {
    cin >> a;
    all.modify(i, a);
    vs[i / K].emplace(a, i);
  }

  const auto calc = [&](int bi) {
    int a, i;
    while (true) {
      tie(a, i) = vs[bi].top();
      if (a == all.get(i)) break;
      vs[bi].pop();
    }
    block.modify(bi, a +
      max(all.query(max(0, i - K + 1), i),
          all.query(i + 1, min(N, i + K))));
  };

  for (int i = 0; i * K < N; ++i) calc(i);

  int pans;
  cout << (pans = block.val[1]) << '\n';

  for (int i, x; Q --> 0; ) {
    cin >> i >> x;
    i = (i ^ pans) - 1; x ^= pans;
    all.modify(i, x);
    int bi = i / K;
    vs[bi].emplace(x, i);
    calc(bi);
    if (bi > 0) calc(bi - 1);
    if (bi + 1 < B) calc(bi + 1);
    cout << (pans = block.val[1]) << '\n';
  }

  return 0;
}
