// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;
const int N = 1e5 + 225;
int n;
int he[N], to[N*2], we[N*2], pr[N*2], ec = 1;

struct FS{
	int fir, sec;
	FS(int f = 0, int s = 0): fir(f), sec(s){}
	void operator()(int x){
		if(x == fir) return;
		if(x > fir) swap(x, fir);
		if(x > sec) swap(x, sec);
	}
} ans;

FS dfs(int u, int p){
	FS dpu;
	for(int e = he[u]; e; e = pr[e]){
		int v = to[e], w = we[e];
		if(v == p) continue;
		FS dpv = dfs(v, u);

		ans(dpu.fir + dpv.fir + w);
		ans(dpu.sec + dpv.fir + w);
		ans(dpu.fir + dpv.sec + w);

		dpu(dpv.fir + w);
		dpu(dpv.sec + w);
	}
	return dpu;
}

int main(){
	n = R();
	for(int u, v, w, i = 1; i < n; ++i){
		u = R(), v = R(), w = R();
		to[ec] = v; we[ec] = w; pr[ec] = he[u]; he[u] = ec++;
		to[ec] = u; we[ec] = w; pr[ec] = he[v]; he[v] = ec++;
	}

	dfs(0, -1);

	W(ans.sec);
	return 0;
}
