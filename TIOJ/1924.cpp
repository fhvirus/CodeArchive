#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#include<algorithm>
using namespace std;
#define MAXN 2000001

int n, ans;

int c, e, p,
	ce, cp, ec, ep, pc, pe,
	cep, cpe, ecp, epc, pce, pec;

int main(){
	n = R();
	char eek = readchar();
	while(eek != 'P' and eek != 'E' and eek != 'C') eek = readchar();
	for(; n; --n){
		cep = max(cep, ce) + (eek == 'P');
		cpe = max(cpe, cp) + (eek == 'E');
		ecp = max(ecp, ec) + (eek == 'P');
		epc = max(epc, ep) + (eek == 'C');
		pce = max(pce, pc) + (eek == 'E');
		pec = max(pec, pe) + (eek == 'C');

		ce = max(ce, c) + (eek == 'E');
		cp = max(cp, c) + (eek == 'P');
		ec = max(ec, e) + (eek == 'C');
		ep = max(ep, e) + (eek == 'P');
		pc = max(pc, p) + (eek == 'C');
		pe = max(pe, p) + (eek == 'E');

		c += (eek == 'C');
		e += (eek == 'E');
		p += (eek == 'P');

		eek = readchar();
	}
	ans = max(max(cep, cpe), max(max(ecp, epc), max(pce, pec)));
	printf("%d\n", ans);
	return 0;
}