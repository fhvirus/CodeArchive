#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  auto operator <=> (const P& o) const = default;
};
typedef Point<int> P;
const int INF = INT_MAX / 2;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  if (K <= 2) { cout << 0 << endl; exit(0); }

  vector<P> ps(N);
  for (auto &[x, y] : ps) cin >> x >> y;
  ranges::sort(ps);

  int ans = INF;
  for (int s = 0; s + K <= N; ++s) {
    vector<P> cand(begin(ps) + s + 1, end(ps));
    ranges::sort(cand, [&](P a, P b) { return ps[s].cross(a, b) > 0; });
    cand.insert(begin(cand), {ps[s]});

    int n = (int)size(cand);
    vector dp(n, vector(n, INF));
    auto sc = dp;
    for (int i = 1; i + (K - 1) <= n; ++i)
      sc[0][i] = 0;
    for (int r = 3; r <= K; ++r) {
      for (auto &i : dp) ranges::fill(i, INF);
      for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) if (sc[i][j] < INF)
        for (int k = j + 1; k < n; ++k) if (cand[i].cross(cand[j], cand[k]) > 0)
          dp[j][k] = min(dp[j][k], sc[i][j] + cand[0].cross(cand[j], cand[k]));
      swap(dp, sc);
    }
    for (auto &i : sc)
      ans = min(ans, *ranges::min_element(i));
  }

  cout << (ans == INF ? 0 : ans / 2) << endl;

  return 0;
}
