#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n,char e){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

const int kN = 1000001;
int N, Q;
int par[kN], wei[kN];
int he[kN], to[kN], pr[kN];

int in[kN], ou[kN], tot;
int euler[kN];
void dfs(int u, int p){
	in[u] = ++tot;
	euler[tot] = u;
	for(int e = he[u]; e != 0; e = pr[e]){
		if(to[e] != p)
			dfs(to[e], u);
	}
	ou[u] = tot;
}

int bit[kN];
inline void modify(int p, int v){
	for(; p <= N; p += p & -p)
		bit[p] += v;
}
inline int query(int p){
	int ans = 0;
	for(; p > 0; p -= p & -p)
		ans += bit[p];
	return ans;
}

signed main(){
	N = R(); Q = R();
	for(int u, v, w, i = 1; i < N; ++i){
		u = R(); v = R(); w = R();
		par[v] = u; wei[v] = w;
		to[i] = v; pr[i] = he[u]; he[u] = i;
	}
	dfs(0, 0);
	for(int i = 1; i <= N; ++i){
		bit[i] += wei[euler[i]];
		if((i + (i & -i)) <= N)
			bit[i + (i & -i)] += bit[i];
	}

	for(int cmd, d, m, i = 0; i < Q; ++i){
		cmd = R();
		if(cmd == 0){
			d = R(); m = R();
			int tmp = m - wei[d];
			modify(in[d], tmp);
			wei[d] = m;
		} else {
			d = R();
			int ans = query(ou[d]) - query(in[d]);
			W(ans * 2, '\n');
		}
	}
	write(1,OB,OP);
	return 0;
}
