#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
#include<cstdio>
const int N = 1001, M = 10000001;
int n, m, a[N];
char in[N];
char adj[N][N];
int main(){
	while(true){
		n = R(), m = R();
		if(n == 0) break;
		for(int a, b; m; --m) a = R(), b = R(), ++adj[a][b], ++in[b];

		bool ans = true;
		for(int i = 1; i <= n; ++i) a[i] = R();
		for(int i = 1; i <= n and ans; ++i){
			if(in[a[i]] != 0){ ans = false; break;}
			for(int j = 1; j <= n; ++j)
				in[j] -= adj[a[i]][j];
		}
		puts(ans ? "YES" : "NO");
		for(int i = 1; i <= n; ++i){
			in[i] = 0;
			for(int j = 1; j <= n; j += 2)
				adj[i][j] = 0;
		}
	}
	return 0;
}