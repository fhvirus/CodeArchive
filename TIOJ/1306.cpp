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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
inline int RS(char* s){
	int p = 1;
	while((s[0] = readchar()) > 'z' or s[0] < 'a');
	for(; (s[p] = readchar()) <= 'z' and s[p] >= 'a'; ++p);
	return p;
}

const int N = 10000;
const long long P = 31, M = 1004535809;
int T, q;
long long h[N+1], jizz, mpow[N+1];
char t[N], p[N];
int lent, lenp;

inline void hash_t(){
	h[0] = 0;
	for(int i = 0; i < lent; ++i){
		h[i] = (h[i] + t[i]) % M;
		h[i+1] = (h[i] * P) % M;
	}
}
inline long long subhash(int a, int b){
	return a == 0 ? h[b-1] : (h[b-1] - h[a-1] * mpow[b - a] % M + M) % M;
}
inline int hash_p(){
	long long ans = 0;
	for(int i = 0; i < lenp; ++i)
		ans = (ans * P + p[i]) % M;
	return ans;
}

int main(){
	mpow[0] = 1;
	for(int i = 1; i <= N; ++i) mpow[i] = mpow[i-1] * P % M;
	T = R();
	for(; T; --T){
		lent = RS(t);
		hash_t();
		q = R();
		for(; q; --q){
			lenp = RS(p);
			jizz = hash_p();
			int ans = 0;
			for(int i = 0; i <= lent - lenp; ++i){
				int eek = subhash(i, i + lenp);
				ans += (eek == jizz);
			}
			printf("%d\n", ans);
		}
	}
}