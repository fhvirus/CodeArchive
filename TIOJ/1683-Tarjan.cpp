// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
using namespace std;
#define FOO(i,a,b) for(int i = a; i <= b; ++i)
#define pb push_back
const int N = 10005, M = 1e5;
int t, n, m;
int head[N], prv[M], to[M];
int sch[N], scp[M], sco[M];
int pre[N], low[N], owo, scc[N], scz[N];
int stk[N], top;
bool ins[N];
int ans[N];
void tarjan(int u){
	pre[u] = low[u] = ++owo;
	stk[top++] = u, ins[u] = true;
	for(int v = head[u]; v != -1; v = prv[v]){
		if(pre[to[v]] == 0){
			tarjan(to[v]);
			low[u] = min(low[u], low[to[v]]);
		}
		else if(ins[to[v]])
			low[u] = min(low[u], pre[to[v]]);
	}
	if(low[u] == pre[u]){
		scz[u] = 0;
		sch[u] = -1;
		int v;
		do{
			v = stk[--top];
			ins[v] = false;
			scc[v] = u;
			++scz[u];
		} while(v != u);
	}
}
int dfs(int u){
	int eek = 0;
	for(int v = sch[u]; v != -1; v = scp[v]){
		eek = max(eek, ans[sco[v]] ? ans[sco[v]] : dfs(sco[v]));
	}
	return ans[u] = eek + scz[u];
}
void solve(){
	n = R(), m = R();
	FOO(i,1,n) head[i] = -1;
	for(int i = 0, j = 0, u, v; i < m; ++i){
		u = R(), v = R();
		to[j] = v; prv[j] = head[u]; head[u] = j++;
	}
	top = 0; owo = 0;
	fill(pre, pre + n + 1, 0);
	FOO(i,1,n) if(pre[i] == 0) tarjan(i);

	int egg = 0;
	FOO(i,1,n)
		for(int j = head[i]; j != -1; j = prv[j])
			if(scc[i] != scc[to[j]]){
				sco[egg] = scc[to[j]];
				scp[egg] = sch[scc[i]];
				sch[scc[i]] = egg++;
			}	

	int eek = 0;
	fill(ans, ans + n + 1, 0);
	FOO(i,1,n) if(scc[i] == i and ans[i] == 0){
		eek = max(eek, dfs(i));
	}
	W(eek);
}
int main(){
	for(t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
