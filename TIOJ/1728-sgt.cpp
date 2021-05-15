// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return -1;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 10000001, Q = 500000;

short cnt[N];
struct Query{ int l, r; } q[Q];
int qs, mr;
int sg[N * 2];

inline int max(int a, int b){ return a > b ? a : b;}
inline int min(int a, int b){ return a < b ? a : b;}
inline int mx(int a, int b){
	if(cnt[a] != cnt[b]) return cnt[a] > cnt[b] ? a : b;
	return a > b ? a : b;
}

void init(){
	cnt[0] = 500;
	for(int i = 1; i <= mr; ++i) cnt[i] = 1;
	for(int i = 2; i <= mr; ++i){
		if(cnt[i] != 1) continue;
		cnt[i] = 2;
		for(int j = i + i; j <= mr; j += i){
			int k = j / i, tmp = 2, g;
			while(true){
				g = k / i;
				if(k - g * i == 0) k = g, ++tmp;
				else break;
			}
			cnt[j] *= tmp;
		}
	}
}

int que(int l, int r){
	int ans = l;
	for(l += mr, r += mr; l < r; l >>= 1, r >>= 1){
		if(l & 1) ans = mx(ans, sg[l++]);
		if(r & 1) ans = mx(ans, sg[--r]);
	}
	return ans;
}

signed main(){
	int a, b, d;
	while(a = R(), b = R(), a != -1 and b != -1){
		if(a > b) d = a, a = b, b = d;
		q[qs] = {a, b}, ++qs;
		mr = max(mr, b);
	}

	init();

	for(int i = 0; i <= mr; ++i) sg[i + mr] = i;
	for(int i = mr - 1; i > 0; --i) sg[i] = mx(sg[i << 1], sg[i << 1 | 1]);

	for(int i = 0; i < qs; ++i) W(que(q[i].l, q[i].r + 1));

	write(1,OB,OP);
	return 0;
}
