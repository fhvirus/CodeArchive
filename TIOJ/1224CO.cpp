#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 1<<20;
int sum[N<<1];
int len[N<<1];
void pull(int p){
	for(int h = 0; p > 0; p >>= 1, ++h)
		len[p] = sum[p] ? 1<<h : (h ? len[p<<1] + len[p<<1|1] : 0);
}
inline void modify(int l, int r, int v){
	int tl = l, tr = r, h = 0;
	for(l += N, r += N; l < r; l >>= 1, r >>= 1, ++h){
		if(l&1){
			sum[l] += v;
			len[l] = sum[l] ? 1<<h : (h ? len[l<<1] + len[l<<1|1] : 0);
			++l;
		}
		if(r&1){
			--r;
			sum[r] += v;
			len[r] = sum[r] ? 1<<h : (h ? len[r<<1] + len[r<<1|1] : 0);
		}
	}
	pull(tl + N), pull(tr-1 + N);
}

#include<algorithm>
using namespace std;
struct edge{
	int x, u, d, lr;
} E[200000];
int main(){
	int n = R(), k = 0;
	for(int i = 0, l, r, d, u; i < n; ++i){
		l = R(); r = R();
		d = R(); u = R();
		E[k++] = (edge){l, u, d, 1};
		E[k++] = (edge){r, u, d, -1};
	}
	sort(E, E + k, [](edge a, edge b){return a.x < b.x;});
	int prex = 0;
	long long ans = 0;
	for(int i = 0; i < k; ++i){
		ans += 1ll * len[1] * (E[i].x - prex);
		modify(E[i].d, E[i].u, E[i].lr);
		prex = E[i].x;
	}
	W(ans);
	return 0;
}