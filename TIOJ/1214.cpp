#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#define llu unsigned long long
const int N = 100 + 1, M = 1e9 + 7;
int n, s1[N], s2[N];
vector<int> g1[N], g2[N];

int getCentroid(vector<int> g[], int s[], int u, int p){
	int sz = 1, mx = 0, tmp;
	for(int v: g[u])
		if(v != p){
			tmp = getCentroid(g, s, v, u);
			mx = max(mx, tmp), sz += tmp;
		}
	mx = max(mx, n - sz);
	s[u] = mx;
	return sz;
}
llu hashtree(vector<int> g[], int u, int p){
	llu ans = 131, tmp;
	for(int v: g[u])
		if(v != p) tmp = hashtree(g, v, u), ans = (ans + (tmp * tmp) % M) % M;
	return ans;
}

int main(){
	while((n = R()) != 0){
		for(int i = 1; i <= n; ++i)
			g1[i].clear(), g2[i].clear();

		for(int i = 0, a, b; i < n-1; ++i){
			a = R(), b = R();
			g1[a].push_back(b);
			g1[b].push_back(a);
		}
		for(int i = 0, a, b; i < n-1; ++i){
			a = R(), b = R();
			g2[a].push_back(b);
			g2[b].push_back(a);
		}
		getCentroid(g1, s1, 1, 0);
		getCentroid(g2, s2, 1, 0);
		int cen1 = 1, cen2 = 1;
		for(int i = 1; i <= n; ++i){
			if(s1[i] < s1[cen1]) cen1 = i;
			if(s2[i] < s2[cen2]) cen2 = i;
		}

		llu h1 = hashtree(g1, cen1, cen1),
			h2 = hashtree(g2, cen2, cen2);

		if(h1 == h2) puts("Same");
		else{
			for(int i = cen2 + 1; i <= n; ++i)
				if(s2[i] == s2[cen2])
					cen2 = i;
			h2 = hashtree(g2, cen2, cen2);

			puts(h1 == h2 ? "Same" : "Different");
		}
	}
}