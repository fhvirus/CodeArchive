#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<cstdio>
#include<cstring>
#include<algorithm>
inline char readchar(){
	const int S = 1<<18;
	static char buf[S], *p = buf, *q = buf;
	return (p == q and (q = (p = buf) + fread(buf, 1, S, stdin)) == buf) ? EOF : *p++;

}
inline int R(){
	int ans = 0; char c = readchar();
	while(c < '0') c = readchar();
	while(c >= '0') ans = ans * 10 + (c ^ '0'), c = readchar();
	return ans;
}

const int N = 1e5 + 1;
int n;
struct seg{
	int l, r, c;
} s[N];

// IterSegTree
int val[N<<1], tag[N];
#define lg(n) 31 - __builtin_clz(n)
void upd(int p, int v, int h){
	val[p] += v<<h;
	if(p < N) tag[p] += v;
}
void push(int p){
	for(int h = lg(N); h >= 0; --h){
		int i = p>>h;
		if(tag[i>>1] == 0) continue;
		upd(i  , tag[i>>1], h);
		upd(i^1, tag[i>>1], h);
		tag[i>>1] = 0;
	}
}
void pull(int p){
	for(int h = 0; p > 1; ++h, p >>= 1)
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

// Ins
int stkl[N], stkr[N], top;
void ins(int l, int r, int c){
	c -= query(l, r);
	if(c <= 0) return;
	int p = r;
	while(top > 0 and p - stkr[top-1] <= c){
		c -= p - stkr[top-1];
		p = stkl[top-1];
		modify(stkl[top-1], stkr[top-1], -1);
		--top;
	}
	modify(p-c, r, 1);
	stkl[top] = p-c, stkr[top] = r, ++top;
}

int main(){
	while((n = R()) != 0){
		for(int i = 0; i < n; ++i) s[i] = {R(), R(), R()};
		std::sort(s, s + n, [](seg a, seg b){return a.r < b.r;});
		top = 0; memset(val, 0, sizeof val); memset(tag, 0, sizeof tag);
		for(int i = 0; i < n; ++i) ins(s[i].l, s[i].r, s[i].c);
		int ans = 0;
		for(int i = 0; i < top; ++i) ans += stkr[i] - stkl[i];
		printf("%d\n", ans);
	}
}