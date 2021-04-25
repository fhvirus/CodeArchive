//Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int,int> pii;

#define AI(x) (x).begin(),(x).end()
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define pb emplace_back
void chmin(int &a, int b){ if(a > b) a = b;}

const int N = 1e5 + 225, L = 17;
int n, q;
int he[N], to[N*2], we[N*2], pr[N*2], ecnt;
int anc[L][N], mne[L][N], dep[N];

struct DSU{
	int n;
	vector<int> d;
	void init(int _n){
		n = _n;
		d.resize(n + 1);
		FOO(i,1,n) d[i] = i;
	}
	int find(int a){
		return a == d[a] ? a : d[a] = find(d[a]);
	}
	bool onion(int a, int b){
		if(find(a) == find(b)) return false;
		d[d[b]] = d[a];
		return true;
	}
};

void dfs(int u, int p){
	for(int i = he[u]; i != -1; i = pr[i]){
		if(to[i] == p) continue;
		anc[0][to[i]] = u;
		mne[0][to[i]] = we[i];
		dep[to[i]] = dep[u] + 1;
		dfs(to[i], u);
	}
}

int main(){
	n = R(), q = R();
	FOO(i,1,n) he[i] = -1;
	DSU dsu;
	dsu.init(n);
	for(int i = n; i >= 1; --i){
		for(int j = i * 2; j <= n; j += i){
			if(dsu.onion(i, j)){
				to[ecnt] = j;
				we[ecnt] = i;
				pr[ecnt] = he[i];
				he[i] = ecnt++;
				to[ecnt] = i;
				we[ecnt] = i;
				pr[ecnt] = he[j];
				he[j] = ecnt++;
			}
		}
	}
	dfs(1, 1);
	for(int i = 1; i < L; ++i){
		FOO(j,1,n){
			anc[i][j] = anc[i-1][anc[i-1][j]];
			mne[i][j] = min(mne[i-1][j], mne[i-1][anc[i-1][j]]);
		}
	}
	for(int a, b, d, m; q; --q){
		a = R(), b = R();
		if(dep[a] < dep[b]) swap(a, b);
		d = dep[a] - dep[b];
		m = 2147483647;
		for(int i = L - 1; i >= 0; --i){
			if((d>>i) & 1) chmin(m, mne[i][a]), a = anc[i][a];
		}
		if(a == b){
			W(m);
			continue;
		}
		for(int i = L - 1; i >= 0; --i){
			if(anc[i][a] != anc[i][b]){
				chmin(m, mne[i][a]);
				chmin(m, mne[i][b]);
				a = anc[i][a];
				b = anc[i][b];
			}
		}
		W(min({m, mne[0][a], mne[0][b]}));
	}
	write(1,OB,OP);

	return 0;
}
