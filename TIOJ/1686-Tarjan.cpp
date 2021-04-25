//Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
using namespace std;

#define FOO(i,a,b) for(int i = a; i <= b; ++i)
#define pb emplace_back

const int N = 2e4 + 225;
int n, m;
vector<int> adj[N];
int pre[N], low[N], owo;
int stk[N], top;
bool ins[N];
int scc[N], cnt;
int siz[N];

void tarjan(int u){
	pre[u] = low[u] = ++owo;
	stk[top++] = u, ins[u] = true;
	for(int v: adj[u]){
		if(!pre[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if(ins[v]) low[u] = min(low[u], pre[v]);
	}
	if(low[u] == pre[u]){
		int v;
		++cnt;
		do{
			v = stk[--top];
			ins[v] = false;
			scc[v] = cnt;
			++siz[cnt];
		}while(v != u);
	}
}

int main(){
	n = R(), m = R();
	for(int a, b, s; m; --m){
		a = R(), b = R(), s = R();
		if(s == 0){
			adj[a].pb(b);
			adj[b + n].pb(a + n);
		} else {
			adj[a].pb(b + n);
			adj[b + n].pb(a);
		}
	}

	FOO(i,1,2*n) if(!pre[i]) tarjan(i); 

	FOO(i,1,n) if(scc[i] == scc[i + n]) --siz[scc[i]];

	FOO(i,1,n) W(siz[scc[i + n]] - 1);
	write(1,OB,OP);
	return 0;
}
