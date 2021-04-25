#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

inline bool getCommand(){
	// 0: Masuta -> Union
	// 1: Kuiin  -> Find
	char c = readchar();
	while(c != 'M' and c != 'K') c = readchar();
	return c == 'M';
}

const int N = 1e5+1;
int n, q, dsu[N];

inline int Find(int a){
	return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
}
inline void Union(int a, int b){
	if(Find(a) == Find(b)) return;
	dsu[Find(b)] = Find(a);
}

int main(){
	n = R(); q = R();
	for(int i = 1; i <= n; ++i) dsu[i] = i;
	for(int a, b; q; --q){
		if(getCommand()){
			a = R(); b = R();
			Union(a, b);
		} else {
			a = R();
			W(Find(a));
		}
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}