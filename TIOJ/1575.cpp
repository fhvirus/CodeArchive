// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int kN = 1000001;
int n, m, k;
int he[kN], to[kN*2][2];

int left;
int dfs(int u, int p, int lim){
	int mx = -kN, mn = kN;
	for(int i = he[u]; i != 0; i = to[i][1]){
		int v = to[i][0];
		if(v == p) continue;
		int d = dfs(v, u, lim);
		if(left < 0) return 0;
		mx = (d > mx ? d : mx);
		mn = (d < mn ? d : mn);
	}
	if(mx + 1 >= lim){
		--left;
		return -lim;
	}
	if(mx < 0) return (mn + 1 < 0 ? mn + 1 : 0);
	if(-mn - 2 >= mx) return mn + 1;
	return mx + 1;
}

signed main(){
	n = R(); m = R(); k = R();
	if(k >= n){ W(0); return 0; }

	for(int u, v, i = 0, j = 1; i < m; ++i){
		u = R(); v = R();
		to[j][0] = v; to[j][1] = he[u]; he[u] = j++;
		to[j][0] = u; to[j][1] = he[v]; he[v] = j++;
	}

	int l = 1, r = n, mid;
	while(l < r){
		mid = (l + r) / 2;

		left = k;
		int d = dfs(1, 1, mid);
		if(d > 0) --left;

		if(left >= 0) r = mid;
		else l = mid + 1;
	}
	W(l);
	return 0;
}
