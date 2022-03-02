#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
char OB[65536]; int OP;
inline void W(int n,char e){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

#include <bitset>

const int kN = 1000001;
int n, m;
int he[kN], es[kN][3];

int pre[kN], low[kN], tot;
std::bitset<kN> ins;
int stk[kN], top;

int scc[kN], cnt;
void dfs(int u) {
	pre[u] = low[u] = ++tot;
	ins[u] = true; stk[++top] = u;
	for (int e = he[u], v = es[e][1]; e; e = es[e][2], v = es[e][1])
		if (pre[v] == 0) {
			dfs(v);
			if (low[v] < low[u])
				low[u] = low[v];
		} else if (ins[v] and pre[v] < low[u])
			low[u] = pre[v];

	if (low[u] == pre[u]) {
		++cnt;
		int v;
		do {
			v = stk[top--];
			ins[v] = false;
			scc[v] = cnt;
		} while (v != u);
	}
}

int scche[kN], scces[kN][2], indeg[kN];
int q[kN], h, t;
int topo[kN], num;

int main() {
	n = R(); m = R();
	for (int u, v, i = 1; i <= m; ++i) {
		u = R(); v = R();
		es[i][0] = u;
		es[i][1] = v;
		es[i][2] = he[u];
		he[u] = i;
	}

	for (int i = 1; i <= n; ++i)
		if (pre[i] == 0) dfs(i);

	for (int i = 1, j = 1, u, v; i <= m; ++i) {
		u = scc[es[i][0]];
		v = scc[es[i][1]];
		if (u == v) continue;
		scces[j][0] = v;
		scces[j][1] = scche[u];
		scche[u] = j++;
		++indeg[v];
	}

	for (int i = 1; i <= cnt; ++i)
		if (indeg[i] == 0) q[t++] = i;

	while (h < t) {
		int u = q[h++];
		topo[u] = ++num;
		for (int e = scche[u], v = scces[e][0]; e; e = scces[e][1], v = scces[e][0]) {
			--indeg[v];
			if (indeg[v] == 0)
				q[t++] = v;
		}
	}

	W(cnt, '\n');
	for (int i = 1; i <= n; ++i)
		W(topo[scc[i]], ' ');
	write(1, OB, OP);

	return 0;
}
