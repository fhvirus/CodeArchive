#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 10000;
bool isprime[N+1];
int p[N], e;
void shai(){
	for(int i = 2; i <= N; ++i) isprime[i] = true;
	isprime[0] = isprime[1] = false;
	for(int i = 2; i <= N; ++i){
		if(isprime[i]) p[e++] = i;
		for(int j = 0; j < e; ++j){
			if(i * p[j] > N) break;
			isprime[i * p[j]] = false;
			if(i % p[j] == 0) break;
		}
	}
}

int n, a, b, cnt;
bool jizz;
int main(){
	shai();
	n = R();
	for(; n; --n){
		a = R();
		if(a == 1){ outbuf[outp++] = '('; outbuf[outp++] = '1'; outbuf[outp++] = ')'; outbuf[outp++] = '\n'; continue;}
		jizz = false;
		for(int i = 0; p[i] <= a; ++i){
			b = a; cnt = 0;
			while(b >= p[i]){
				cnt += b / p[i];
				b /= p[i];
			}
			if(cnt > 0){
				if(jizz) outbuf[outp++] = '*';
				jizz = true;
				if(cnt > 1)
					outbuf[outp++] = '(',
					W(p[i]),
					outbuf[outp++] = '^',
					W(cnt),
					outbuf[outp++] = ')';
				else
					outbuf[outp++] = '(',
					W(p[i]),
					outbuf[outp++] = ')';
			}
		}
		outbuf[outp++] = '\n';
	}
	fwrite(outbuf, 1, outp, stdout);
}