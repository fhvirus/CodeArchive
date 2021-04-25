#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#include<unistd.h>
const int S = 65536;
char OB[S]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[5],p;p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>S-12)write(1,OB,OP),OP=0;}
inline int max(int a, int b){return a>b?a:b;}
const int N = 501, M = 1024 + 10;
short m, cnt[N], adj[N][N];
int ans[M], ptr, n;

void dfs(int u){
	for(int v = 1; v <= n; ++v)
		if(adj[u][v] > 0){
			adj[u][v]--, adj[v][u]--;
			dfs(v);
		}
	ans[ptr++] = u;
}

int main(){
	while((m = R()) != 0){
		ptr = 0, n = 0;
		for(int i = 1; i < N; ++i)
			cnt[i] = 0;
		for(int i = 0, a, b; i < m; ++i){
			a = R(), b = R();
			n = max(n, max(a, b));
			cnt[a]++, cnt[b]++;
			adj[a][b]++, adj[b][a]++;
		}
		int s = N;
		for(int i = 1; i < n; ++i)
			if(cnt[i] & 1){ s = i; break;}
		if(s == N) s = 1;

		dfs(s);
		for(ptr--; ptr >= 0; --ptr)
			W(ans[ptr]);
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
}