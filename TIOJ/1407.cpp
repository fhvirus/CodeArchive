#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

inline int min(int a, int b){ return a < b ? a : b;}
inline void eek(int &a, int b){ if(a < b) a = b ;}

const int N = 1e6;
int n, t, e, ans, dp[N+1], lim;
int ww[N], mm[N];

inline void upd(int w, int m){
	for(int j = min(t, lim) - w; j >= 0; --j)
		eek(dp[j + w], dp[j] + m);
}

int main(){
	n = R();
	for(int i = 0, w, m, c; i < n; ++i){
		w = R(), m = R(), c = R();
		for(int j = 1; j <= c; c -= j, j<<=1)
			ww[e] = w*j, mm[e] = m*j, e++;
		if(c) ww[e] = w*c, mm[e] = m*c, e++;
	}
	t = R();
	for(int i = 0; i < e; ++i){
		if(lim < t) lim += ww[i];
		upd(ww[i], mm[i]);
	}
	for(int i = 0; i <= t; ++i)
		eek(ans, dp[i]);
	W(ans);
}