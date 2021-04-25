#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
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
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = ' '; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = ' ';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

int n, k, a[2048][2048];

int main(){
	n = getchar_unlocked() - '0';
	if(n == 1) k = getchar_unlocked();
	if(k != EOF) n = n*10 + k - '0';
	k = 1<<n;
	a[0][0] = 0;
	a[1][1] = 3;
	a[1][0] = ((n&1) ? 1 : 2);
	a[0][1] = 3 - a[1][0];

	for(int i = 0; i < k; ++i){
		for(int j = 0; j < k; ++j)
			W(a[i][j]);
		outbuf[outp++] = '\n';
	}
	fwrite(outbuf, 1, outp, stdout);
}