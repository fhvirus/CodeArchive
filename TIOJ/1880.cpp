// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 1e5 + 225, M = 1e6 + 7;

int pow2(int e){
	long long r = 1, x = 2;
	while(e) (e&1)&&(r=r*x%M), (x=x*x%M), e>>=1;
	return r;
}

int n, m;
int sz, bip[N*2];
int fbip(int a){ return a == bip[a] ? a : bip[a] = fbip(bip[a]);}
inline bool ubip(int a, int b){
	if(fbip(a) == fbip(b)) return false;
	bip[bip[b]] = bip[a];
	return true;
}

int main(){
	n = R(), m = R(), sz = n;
	for(int i = 0; i <= n*2; ++i) bip[i] = i;
	for(int u, v; m; --m){
		u = R(), v = R();
		if(!ubip(u, v + n)){
			W(0);
			return 0;
		}
		ubip(u + n, v);
		--sz;
	}
	W(pow2(sz - 1));
	return 0;
}
