// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii;
#define pb emplace_back
const int N = 100000, L = 18;

int n, q;
int he[N], pr[N*2];
pii to[N*2];

int siz[N];
int eek[N], tot;
bool vis[N];
int com[N], top;

int dep[N];
int par[N];
ll dis[N][L];

int getSiz(int u, int p){
	siz[u] = 1; com[top++] = u;
	for(int e = he[u], v; e != -1; e = pr[e]){
		v = to[e].first;
		if(!vis[v] and v != p)
			siz[u] += getSiz(v, u);
	}
	return siz[u];
}
int getCen(int u, int p, int s){
	for(int e = he[u], v; e != -1; e = pr[e]){
		v = to[e].first;
		if(!vis[v] and v != p and siz[v] * 2 > s)
			return getCen(v, u, s);
	}
	return u;
}
void getDis(int u, int d){
	vis[u] = true;
	for(int e = he[u], v, w; e != -1; e = pr[e]){
		tie(v, w) = to[e];
		if(!vis[v]) dis[v][d] = dis[u][d] + w, getDis(v, d);
	}
}
void cenDecomp(int u, int d, int p){
	getSiz(u, p);

	int cen = getCen(u, p, siz[u]);

	dis[cen][d] = 0;
	getDis(cen, d);
	for(int i = 0; i < top; ++i) vis[com[i]] = false;
	top = 0;

	vis[cen] = true;
	dep[cen] = d;
	par[cen] = p;

	for(int e = he[cen], v, w; e != -1; e = pr[e]){
		tie(v, w) = to[e];
		if(!vis[v]) cenDecomp(v, d + 1, cen);
	}
}

bool has[N];
int cnt[N];
ll sum[N];
void upd(int u){
	if(has[u]) return;
	has[u] = true;
	for(int d = dep[u], p = u; p != -1; p = par[p], --d){
		++cnt[p];
		sum[p] += dis[u][d] - dis[u][d-1];
	}
}
ll query(int u){
	ll ans = 0;
	int lsz = 0;
	for(int d = dep[u], p = u; p != -1; p = par[p], --d){
		ans += sum[p] + (cnt[p] - lsz) * dis[u][d];
		lsz = cnt[p];
	}
	return ans;
}

int main(){
	n = R(), q = R();
	for(int i = 0; i < n; ++i) he[i] = -1;
	for(int u, v, w, i = 1, j = 0; i < n; ++i){
		u = R(), v = R(), w = R();
		to[j] = {v, w}; pr[j] = he[u]; he[u] = j++;
		to[j] = {u, w}; pr[j] = he[v]; he[v] = j++;
	}

	cenDecomp(0, 1, -1);

	for(int t, x; q; --q){
		t = R(), x = R();
		if(t == 1) upd(x);
		else W(query(x));
	}
	write(1,OB,OP);
	return 0;
}
