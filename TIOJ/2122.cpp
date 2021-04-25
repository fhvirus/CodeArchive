#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
typedef long long ll;
const int MASK = 0b11111111111111111111111000000000;
const int S = 1<<17;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[7];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

#include<algorithm>
#include<cmath>
using namespace std;
const int N = 1e5;
int n, m, a[N+1], k, l[N], r[N], id[N];
short ans[N];
short cnt[N+1], cntcnt[N+1], mode;
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
	n = R(), m = R();
	for(int i = 1; i <= n; ++i) a[i] = R();
	FOR(i, m) l[i] = R(), r[i] = R(), id[i] = i;
	// k = sqrt((double)n);
	// k = 500;
	sort(id, id + m, [](int a, int b){
		// return l[a]/k != l[b]/k ? l[a]/k < l[b]/k : (((l[a] / k) & 1) ? r[a] > r[b] : r[a] < r[b]);
		return (l[a]&MASK) != (l[b]&MASK) ? (l[a]&MASK) < (l[b]&MASK) : ((l[a] & 512) ? r[a] > r[b] : r[a] < r[b]);
	});
	int L = 0, R = 0;
	FOR(i, m){
		while(L > l[id[i]]) add(a[--L]);
		while(R < r[id[i]]) add(a[++R]);
		while(L < l[id[i]]) sub(a[L++]);
		while(R > r[id[i]]) sub(a[R--]);
		ans[id[i]] = mode;
	}
	FOR(i, m) W(ans[i]);
	fwrite(outbuf, 1, outp, stdout);
}