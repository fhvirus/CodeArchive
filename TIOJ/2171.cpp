#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 501;
int A, B, S, M, K, a[N], b[N];
int dsu[N * 3];
inline int Find(int a){ return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);}
inline void Union(int a, int b){ if(Find(a) != Find(b)) dsu[dsu[b]] = dsu[a];}

int main(){
	A = R(), B = R(), S = R(), M = R(), K = R();
	for(int i = 1; i <= A; ++i)
		dsu[i] = i;
	for(int i = 1; i <= B; ++i)
		dsu[i + N] = i + N;

	for(int i = 0, u, v, c; i < K; ++i){
		u = R(), v = R(), c = R();
		a[u]++, b[v]++;
		Union(u, v + N);
	}
	int ans = 0;
	for(int i = 1; i <= A; ++i){
		if(a[i] > 0 and i == dsu[i]){
			int odd = 0;
			for(int j = 1; j <= A; ++j)
				if(Find(j) == i and a[j] % 2 == 1)
					++odd;
			for(int j = 1; j <= B; ++j)
				if(Find(j + N) == i and b[j] % 2 == 1)
					++odd;
			ans += odd / 2 > 1 ? odd / 2 : 1;
		}
	}
	W(ans);
	return 0;
}