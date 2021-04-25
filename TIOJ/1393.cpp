#pragma Ofast
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[6],OP=0,buf[6],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 10001;
int n, head[N], to[N*2], prv[N*2];
int pre[N], cnt, parent[N];
bool mark[N], cover[N];

void dfs(int u, int p){
	parent[u] = p, pre[cnt++] = u;
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p) dfs(to[v], u);
}

int main(){
	n = R();
	for(int i = 1; i <= n; ++i)
		head[i] = -1;
	for(int i = 1, a, b, j = 0; i < n; ++i){
		a = R(), b = R();
		to[j] = b, prv[j] = head[a], head[a] = j++;
		to[j] = a, prv[j] = head[b], head[b] = j++;
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = n-1, u, p; i >= 0; --i){
		u = pre[i], p = parent[u];
		if(!cover[u] and !mark[p]){
			mark[p] = true;
			cover[u] = cover[p] = cover[parent[p]] = true;
			++ans;
		}
	}
	W(ans);
}