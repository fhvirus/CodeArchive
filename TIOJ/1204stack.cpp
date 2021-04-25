#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
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
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = ' '; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = ' ';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 1e4;
int n, a[N], l[N], r[N], lc[N], rc[N], root;
int s[N], top;

int main(){
	while((n = R()) != 0){
		top = 0;
		FOR(i, n){
			a[i] = R(), lc[i] = rc[i] = -1;
			while(top > 0 and a[s[top-1]] > a[i]) --top;
			l[i] = top == 0 ? -1 : s[top-1];
			s[top++] = i;
		}

		top = 0;
		for(int i = n-1; i >= 0; --i){
			while(top > 0 and a[s[top-1]] > a[i]) --top;
			r[i] = top == 0 ? -1 : s[top-1];
			s[top++] = i;
		}

		FOR(i, n){
			if(l[i] == -1 and r[i] == -1) root = i;
			else if(l[i] == -1 or (r[i] != -1 and a[l[i]] < a[r[i]])) (i > r[i] ? rc[r[i]] : lc[r[i]]) = i;
			else (i > l[i] ? rc[l[i]] : lc[l[i]]) = i;
		}

		top = 0;
		s[top++] = root;
		while(top > 0){
			int u = s[--top];
			W(a[u]);
			if(rc[u] != -1) s[top++] = rc[u];
			if(lc[u] != -1) s[top++] = lc[u];
		}

		outbuf[outp++] = '\n';
	}
	fwrite(outbuf, 1, outp, stdout);
}