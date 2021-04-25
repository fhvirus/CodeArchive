#include<iostream>
#include<algorithm>
#include<utility>
#include<cstring>
using namespace std;

const int N = 1e5 + 25;
int n;

// Iterative Segment Tree from 2qb^z
int val[N<<1], tag[N];
#define lg(n) 31 - __builtin_clz(n)
void upd(int p, int d, int h){
	val[p] += d<<h;
	if(p < N) tag[p] += d;
}
void push(int p){
	for(int h = lg(N); h >= 0; --h){
		int i = p>>h;
		if(!tag[i>>1]) continue;
		upd(i, tag[i>>1], h);
		upd(i^1, tag[i>>1], h);
		tag[i>>1] = 0;
	}
}
void pull(int p){
	for(int h = 0; p > 1; ++h, p>>=1)
		val[p>>1] = val[p] + val[p^1] + tag[p>>1] * (2 << h);
}
void modify(int l, int r, int v){
	int L = l, R = r, h = 0;
	for(l += N, r += N; l < r; l >>= 1, r >>= 1, ++h){
		if(l&1) upd(l++, v, h);
		if(r&1) upd(--r, v, h);
	}
	pull(L+N), pull(R-1+N); 
}
int query(int l, int r){
	push(l+N), push(r-1+N);
	int ans = 0;
	for(l += N, r += N; l < r; l >>= 1, r >>= 1){
		if(l&1) ans += val[l++];
		if(r&1) ans += val[--r];
	}
	return ans;
}

// Insert
#include<vector>
#define ff first
#define ss second
vector<pair<int, int>> stk;
void ins(int l, int r, int c){
	c -= query(l, r);
	if(c <= 0) return;
	int p = r;
	while(!stk.empty() and p - stk.back().ss <= c){
		c -= p - stk.back().ss;
		p = stk.back().ff;
		modify(stk.back().ff, stk.back().ss, -1);
		stk.pop_back();
	}
	modify(p-c, r, 1);
	stk.push_back({p-c, r});
}

struct seg{
	int l, r, c;
} s[N];
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> n, n){
		for(int i = 0; i < n; ++i) cin >> s[i].l >> s[i].r >> s[i].c;
		sort(s, s + n, [](seg a, seg b){return a.r < b.r;});
		stk.clear();
		memset(val, 0, sizeof val); memset(tag, 0, sizeof tag);
		for(int i = 0; i < n; ++i) ins(s[i].l, s[i].r, s[i].c);
		int sum = 0;
		for(auto i: stk) sum += i.ss - i.ff;
		cout << sum << '\n';
	}
}