#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	short ans = 0; char c = readchar(); bool minus = false;
	while(c<'-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    if(n < 0) outbuf[outp++] = '-', n = -n;
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 1025;
int n,  bit[N*N];
inline void add(int x, int y, int v){
	for(; x <= n; x += x & -x)
		for(int i = y; i <= n; i += i & -i)
			bit[x*n+i] += v;
}
inline int query(int x, int y){
	int ans = 0;
	for(; x > 0; x -= x & -x)
		for(int i = y; i > 0; i -= i & -i)
			ans += bit[x*n+i];
	return ans;
}
int main(){
	n = R();
	int cmd, x1, y1, x2, y2, z;
	while((cmd = R()) != 0){
		cmd == 1
		?
			(x1 = R()+1, y1 = R()+1, z = R(), add(x1, y1, z))
		:
			(x1 = R()+1, y1 = R()+1, x2 = R()+1, y2 = R()+1, W(query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1)))
		;
	}
	fwrite(outbuf, 1, outp, stdout);
}