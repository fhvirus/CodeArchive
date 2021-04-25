#include<cstdio>
#include<set>
using namespace std;

constexpr int MAXN = 2e5 + 1;

set<int> adj[MAXN];
int subSize[MAXN];
int cdDepth[MAXN];
int par[MAXN];
int maxdepth;

inline int readint(){
	int ans = 0;
	char ch = getchar();
	while(true){
		if(ch >= '0' and ch <= '9') break;
		ch = getchar();
	}
	ans = ch - '0';
	while(true){
		ch = getchar();
		if(ch > '9' or ch < '0') break;
		ans = ans * 10 + (ch - '0');
	}
	return ans;
}
inline int max(int a, int b){
	return a > b ? a : b;
}

int getSize(int u, int p){
	subSize[u] = 1;
	for(int v: adj[u]){
		if(v != p)
			subSize[u] += getSize(v, u);
	}
	return subSize[u];
}

int getCentroid(int u, int p, int n){
	for(int v: adj[u]){
		if(v != p and (subSize[v]<<1) > n)
			return getCentroid(v, u, n);
	}
	return u;
}

void centroidDecomposition(int u, int p, int d){
	int n = getSize(u, p);
	int c = getCentroid(u, p, n);
	par[c] = p;
	cdDepth[c] = d;
	maxdepth = max(d, maxdepth);
	for(int v: adj[c]){
		if(v != p){
			adj[v].erase(c);
			centroidDecomposition(v, c, d+1);
		}
	}
	adj[c].clear();
}

int main(){
	int n;
	n = readint();
	for(int i = 1, a, b; i < n; i++){
		a = readint(); b = readint();
		adj[a].insert(b);
		adj[b].insert(a);
	}
	centroidDecomposition(1, 0, 0);
	if(maxdepth >= 26){
		printf("Impossible!\n");
		return 0;
	}
	for(int i = 1; i <= n; i++){
		printf("%c ", cdDepth[i] + 'A');
	}
	return 0;
}