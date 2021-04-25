#pragma GCC optimize("Ofast")
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

const int N = 2e5 + 225;

/* Start Suffix Automaton */
int sz, last;
int ch[N*2][26], len[N*2], par[N*2], cnt[N*2];
int tmp[N*2];
inline void init(){
	len[0] = 0;
	par[0] = -1;
	sz = 1;
	last = 0;
}
inline void add(char c){
	int cur = sz++;
	len[cur] = len[last] + 1;
	cnt[cur] = 1;
	par[cur] = 0;

	int p = last;
	while(p != -1 and ch[p][c] == 0)
		ch[p][c] = cur,
		p = par[p];

	if(p == -1){
		par[cur] = 0;
	} else {
		int q = ch[p][c];
		if(len[p] + 1 == len[q]){
			par[cur] = q;
		} else {
			int clone = sz++;
			len[clone] = len[p] + 1;
			for(int i = 0; i < 26; ++i)
				ch[clone][i] = ch[q][i];
			par[clone] = par[q];
			while(p != -1 and ch[p][c] == q){
				ch[p][c] = clone;
				p = par[p];
			}
			par[q] = par[cur] = clone;
		}
	}

	last = cur;
}
inline void build(string s){
	init();
	for(char c: s) add(c - 'a');
	for(int i = 0; i < sz; ++i) tmp[i] = i;
	sort(tmp, tmp + sz, [](int a, int b){return len[a] > len[b];});
	for(int i = 0; i < sz; ++i) cnt[par[tmp[i]]] += cnt[tmp[i]];
}
/* End Suffix Automaton */

int n;
string s;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> s;
	build(s);
	int ans = 0;
	for(int i = 0; i < sz; ++i)
		if(cnt[i] >= 2) ans = max(ans, len[i]);
	cout << ans;
}