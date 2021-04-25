#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<10;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0' and c != -1) c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[6], eekp;
int outp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
}

const int N = 10001;
short n, m, k, dsu[N];
inline int Find(int a){
	return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);
}
inline void Union(int a, int b){
	dsu[Find(b)] = Find(a);
}
int main(){
	while((n = R()) != 0){
		m = R();
		for(int i = 1; i <= n; ++i) dsu[i] = i;
		for(int a, b; m; --m) a = R(), b = R(), Union(a, b);
		k = Find(R());
		for(int i = 1; i <= n; ++i) if(Find(i) == k){ W(i); break;}
	}
	write(1, outbuf, outp);
}