#pragma GCC optimize("Ofast")
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

const int N = 2e5 + 225;

/* Start SAM */
int sz, last;
struct state{
	int ch[26];
	int len, par;
} st[N * 2];

long long dp[N * 2];
inline void init(){
	st[0].len = 0;
	st[0].par = -1;
	for(int i = 0; i <= sz; ++i){
		st[i].len = 0;
		st[i].par = -1;
		dp[i] = 0;
		for(int j = 0; j < 26; ++j)
			st[i].ch[j] = 0;
	}
	sz = 1;
	last = 0;
}
inline void add(char c){
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	st[cur].par = 0;

	int p = last;
	while(p != -1 and st[p].ch[c] == 0){
		st[p].ch[c] = cur;
		p = st[p].par;
	}
	if(p == -1){
		st[cur].par = 0;
	} else {
		int q = st[p].ch[c];
		if(st[p].len + 1 == st[q].len){
			st[cur].par = q;
		} else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			for(int i = 0; i < 26; ++i)
				st[clone].ch[i] = st[q].ch[i];
			st[clone].par = st[q].par;
			while(p != -1 and st[p].ch[c] == q){
				st[p].ch[c] = clone;
				p = st[p].par;
			}
			st[q].par = st[cur].par = clone;
		}
	}

	last = cur;
}
inline void build(string s){
	init();
	for(char c: s)
		add(c - 'a');
}
/* End SAM */

long long dfs(int u){
	long long ans = 1;
	for(int i = 0, v; i < 26; ++i){
		v = st[u].ch[i];
		if(v != 0){
			if(dp[v]) ans += dp[v];
			else ans += dfs(v);
		}
	}
	return dp[u] = ans;
}
inline long long solve(){
	for(int i = 0; i <= sz; ++i)
		dp[i] = 0;
	return dfs(0);
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string t;
	while(cin >> t){
		build(t);
		cout << solve() << '\n';
	}
	return 0;
}