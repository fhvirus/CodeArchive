#include <bits/stdc++.h>
using namespace std;
 
struct SuffixArray {
	vector<int> sa, rank, lcp;
	SuffixArray (const string& s, const int lim = 256) {
		const int n = s.size();
		vector<int> p(n), c(n), cnt(max(lim, n), 0);
		for (int i = 0; i < n; ++i) ++cnt[s[i]];
		for (int i = 1; i < lim; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) p[--cnt[s[i]]] = i;
 
		c[p[0]] = 0;
		int tot = 1;
		for (int i = 1; i < n; ++i) {
			if (s[p[i]] != s[p[i - 1]]) ++tot;
			c[p[i]] = tot - 1;
		}
 
		vector<int> pn(n), cn(n);
		for (int h = 0; (1 << h) < n; ++h) {
			for (int i = 0; i < n; ++i) {
				pn[i] = p[i] - (1 << h);
				if (pn[i] < 0) pn[i] += n;
			}
 
			fill(begin(cnt), begin(cnt) + tot, 0);
			for (int i = 0; i < n; ++i) ++cnt[c[pn[i]]];
			for (int i = 1; i < tot; ++i) cnt[i] += cnt[i - 1];
			for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
 
			cn[p[0]] = 0;
			tot = 1;
			pair<int, int> prv(c[p[0]], c[(p[0] + (1 << h)) % n]);
			for (int i = 1; i < n; ++i) {
				pair<int, int> cur(c[p[i]], c[(p[i] + (1 << h)) % n]);
				if (prv != cur) ++tot;
				cn[p[i]] = tot - 1;
				prv = cur;
			}
			swap(c, cn);
		}
 
		sa = p;
		rank = c;
 
		int k = 0;
		lcp.assign(n - 1, 0);
		for (int i = 0; i < n; ++i) {
			if (rank[i] == n - 1) {
				k = 0;
				continue;
			}
			int j = p[rank[i] + 1];
			while (i + k < n and j + k < n and s[i + k] == s[j + k]) ++k;
			lcp[rank[i]] = k;
			if (k > 0) --k;
		}
	}
};
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
	string s;
	cin >> s;
	SuffixArray sa(s + '$');
 
	long long ans = (long long) s.size() * (s.size() + 1) / 2;
	for (const int& len: sa.lcp) ans -= len;
 
	cout << ans << '\n';
 
	return 0;
}
