// Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<cassert>
#include<vector>
using namespace std;
#define pb emplace_back
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)

const int N = 2e5 + 225, E = 230032;

int head[N], to[E*2], prv[E*2], e;
int match[N], vis[N], eek;

bool dfs(int u){
	if(vis[u] == eek) return false;
	vis[u] = eek;
	for(int v = head[u]; v != -1; v = prv[v])
		if(!match[to[v]] or dfs(match[to[v]])){
			match[u] = to[v];
			match[to[v]] = u;
			return true;
		}
	return false;
}

int gm(int p){
	int ans = 0;
	FOO(i,1,p) if(!match[i])
		for(int j = head[i]; j != -1; j = prv[j])
			if(!match[to[j]]){
				match[i] = to[j];
				match[to[j]] = i;
				++ans;
				break;
			}
	return ans;
}

void solve(){
	int p, q, k; p = R(), q = R(), k = R(); e = 0;
	FOO(i,1,p + q) head[i] = -1;
	FOO(i,1,p + q) match[i] = 0;
	int ans = 0;
	for(int u, v; k; --k){
		u = R(), v = R() + p;
		to[e] = v; prv[e] = head[u]; head[u] = e++;
	}
	++eek;
	ans += gm(p);
	FOO(i,1,p) if(!match[i]) ++eek, ans += dfs(i);
	W(ans);
}

int main(){
	for(int t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
