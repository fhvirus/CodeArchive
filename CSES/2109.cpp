#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct SuffixArray {
	vi sa, lcp, rank;
	SuffixArray(string& s, int lim=256) {
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		x.push_back(0), sa = lcp = rank = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  ll k;
  cin >> k;

  SuffixArray sa(s);

  vector<vector<tuple<int, int, int>>> segs(sz(sa.sa));
  vector<pii> stk;
  stk.emplace_back(0, 0);
  rep (i, 1, sz(sa.sa)) {
    int len = sa.lcp[i];
    while (stk.back().second > len) {
      auto [last, last_len] = stk.back(); stk.pop_back();
      if (stk.back().second >= len)
        segs[last].emplace_back(stk.back().second + 1, last_len, i - last);
      else {
        segs[last].emplace_back(len + 1, last_len, i - last);
        stk.emplace_back(last, len);
      }
    }
    if (stk.back().second < sz(s) - sa.sa[i])
      stk.emplace_back(i, sz(s) - sa.sa[i]);
  }
  while (sz(stk) > 1) {
    auto [last, last_len] = stk.back(); stk.pop_back();
    segs[last].emplace_back(stk.back().second + 1, last_len, sz(sa.sa) - last);
  }

  rep (i, 1, sz(sa.sa)) {
    while (not segs[i].empty()) {
      auto [l, r, t] = segs[i].back(); segs[i].pop_back();
      ll tot = (ll) t * (r - l + 1);
      if (k <= tot) {
        ll len = l + (k - 1) / t;
        cout << s.substr(sa.sa[i], len) << '\n';
        return 0;
      }
      k -= tot;
    }
  }

  return 0;
}
