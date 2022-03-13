#include<bits/stdc++.h>
using namespace std;
 
struct SuffixArray {
	int n; string s;
	vector<int> sa, rank;
	SuffixArray(const string& _s, const int lim = 256): n(_s.size()), s(_s) {
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
			for (int i = 0; i < n; ++i) ++cnt[c[i]];
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
	}
	bool smaller(const int& pos, const string& t) const {
		string sub = s.substr(pos, min(n - pos, (int) t.size()));
		return sub < t;
	}
	bool contains(const string& t) {
		int pos = -1;
		for (int l = (1 << __lg(n)); l > 0; l >>= 1) {
			if (pos + l < n and smaller(sa[pos + l], t))
				pos += l;
		}
		pos = sa[pos + 1];
		string sub = s.substr(pos, min(n - pos, (int) t.size()));
		return t == sub;
	}
};
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
	string s;
	cin >> s;
 
	SuffixArray sa(s + '$');
 
	int k;
	cin >> k;
 
	while (k --> 0) {
		string t;
		cin >> t;
		cout << (sa.contains(t) ? "YES\n" : "NO\n");
	}
 
	return 0;
}
