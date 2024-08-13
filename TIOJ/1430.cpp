#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K, M;
  cin >> N >> K >> M;

  vi no(N + 2);
  vector<pii> yes;
  for (int A, B, C, i = 0; i < M; ++i) {
    cin >> A >> B >> C;
    if (C == 0) {
      no[A] += 1;
      no[B + 1] -= 1;
    } else yes.emplace_back(A, B);
  }
  partial_sum(all(no), begin(no));

  vi new_id(N + 1, -1), old_id;
  for (int i = 1; i <= N; ++i) {
    if (no[i] == 0)
      old_id.push_back(i);
    new_id[i] = sz(old_id) - 1;
  }

  int C = sz(old_id);
  if (C == K) {
    for (int i : old_id)
      cout << i << '\n';
    return 0;
  }

  {
    vi rb(C, -1);
    for (auto &[l, r] : yes) {
      l = new_id[l] + (new_id[l] == new_id[l - 1]);
      r = new_id[r];
      if (l > r) continue;
      if (rb[l] == -1 or rb[l] > r) rb[l] = r;
    }
    for (int i = C - 1, min_r = C; i >= 0; --i) {
      if (rb[i] >= min_r) rb[i] = -1;
      else if (rb[i] != -1) min_r = rb[i];
    }
    yes.clear();
    rep (i, 0, C) if (rb[i] != -1) yes.emplace_back(i, rb[i]);
  }

  vi ans_l(sz(yes)), ans_r(sz(yes));
  for (int cnt = 0, cur = -1, i = 0; i < sz(yes); ++i) {
    if (cur < yes[i].first)
      cnt += 1, cur = yes[i].second;
    ans_l[i] = cnt;
  }
  for (int cnt = 0, cur = C, i = sz(yes) - 1; i >= 0; --i) {
    if (cur > yes[i].second)
      cnt += 1, cur = yes[i].first;
    ans_r[i] = cnt;
  }

  vi anss;
  for (int prv = -1, i = 0, nxt = 0; i < sz(yes); ++i) {
    auto [l, r] = yes[i];
    while (yes[prv + 1].second < r - 1) prv += 1;
    while (nxt < sz(yes) and yes[nxt].first <= r - 1) nxt += 1;
    if (l == r) { anss.push_back(r); continue; }
    if (i > 0 and ans_l[i] == ans_l[i - 1]) continue;
    int need = (prv >= 0 ? ans_l[prv] : 0)
      + 1 + (nxt < sz(yes) ? ans_r[nxt] : 0);
    if (need > K) anss.push_back(r);
  }

  if (anss.empty()) cout << -1 << '\n';
  for (int i : anss) cout << old_id[i] << '\n';

  return 0;
}
