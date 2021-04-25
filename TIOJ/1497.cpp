#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

vector<int> buildSA(string const& s){
	const int alphabet = 256;
	int n = s.size();
	vector<int> p(n), c(n), cnt(max(n, alphabet), 0);

	// counting sort for 0th iter.
	for(int i = 0; i < n; ++i)
		cnt[s[i]]++;
	for(int i = 1; i < alphabet; ++i)
		cnt[i] += cnt[i-1];
	for(int i = 0; i < n; ++i)
		p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	int classes = 1;
	for(int i = 1; i < n; ++i){
		if(s[p[i]] != s[p[i-1]])
			++classes;
		c[p[i]] = classes - 1;
	}

	// iter through all.
	vector<int> pn(n), cn(n);
	for(int h = 0; (1<<h) < n; ++h){
		for(int i = 0; i < n; ++i){
			pn[i] = p[i] - (1<<h);
			if(pn[i] < 0)
				pn[i] += n;
		}

		fill(cnt.begin(), cnt.begin() + classes, 0);
		for(int i = 0; i < n; ++i)
			cnt[c[pn[i]]]++;
		for(int i = 1; i < classes; ++i)
			cnt[i] += cnt[i-1];
		for(int i = n-1; i >= 0; --i)
			p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		classes = 1;
		for(int i = 1; i < n; ++i){
			if(c[p[i]] != c[p[i-1]] or c[(p[i] + (1<<h)) % n] != c[(p[i-1] + (1<<h)) % n])
				++classes;
			cn[p[i]] = classes - 1;
		}
		c.swap(cn);
	}
	return p;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string s;
	getline(cin, s);
	s.push_back(0);
	vector<int> ans = buildSA(s);
	for(int i = 1; i < ans.size(); ++i){
		cout << ans[i] << '\n';
	}
	return 0;
}