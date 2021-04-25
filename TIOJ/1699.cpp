#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S];
int outp;
inline void W(bool yes){
	if(yes) outbuf[outp++] = 'Y', outbuf[outp++] = 'e', outbuf[outp++] = 's', outbuf[outp++] = '\n';
	else outbuf[outp++] = 'N', outbuf[outp++] = 'o', outbuf[outp++] = '\n';
	if(outp > S - 5) fwrite(outbuf, 1, outp, stdout);
}

#include<algorithm>
#include<cmath>
using namespace std;
const int N = 5e4 + 1;
int n, q, a[N];
int des[N], e;
int l[N], r[N], k[N], id[N];

int cnt[N], cntcnt[N], mode;
inline void add(int v){
	--cntcnt[cnt[v]];
	if(++cnt[v] > mode) mode = cnt[v];
	++cntcnt[cnt[v]];
}
inline void sub(int v){
	--cntcnt[cnt[v]];
	if(cntcnt[mode] == 0) --mode;
	++cntcnt[--cnt[v]];
}

int main(){
	n = R(), q = R();
	for(int i = 1; i <= n; ++i) des[e++] = a[i] = R();
	sort(des, des + e); e = unique(des, des + e) - des;
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(des, des + e, a[i]) - des + 1;

	FOR(i, q) l[i] = R(), r[i] = R(), k[i] = R(), id[i] = i;
	int bsize = n / sqrt(q);
	sort(id, id + q, [&](int a, int b){
		return (l[a] / bsize != l[b] / bsize) ? (l[a] / bsize < l[b] / bsize) : (l[a] / bsize % 2 ? r[a] > r[b] : r[a] < r[b]);
	});

	int lptr = 0, rptr = 0;
	FOR(i, q){
		while(lptr > l[id[i]]) add(a[--lptr]);
		while(rptr < r[id[i]]) add(a[++rptr]);
		while(lptr < l[id[i]]) sub(a[lptr++]);
		while(rptr > r[id[i]]) sub(a[rptr--]);
		if(k[id[i]] == 0){ l[i] = 7122; continue;}
		int len = rptr - lptr + 1;
		int jiz = ceil(len / (double)k[id[i]]);
		l[id[i]] = (mode >= jiz ? 7122 : 0);
	}

	FOR(i, q) W(l[i] == 7122);
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}