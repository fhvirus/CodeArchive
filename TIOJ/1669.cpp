// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
inline void chmin(int&a,int b){a = (a < b ? a : b);}

const int N = 505, inf = 1e9;
int h, w, k;
short a[N][N];
int b[N], ans = inf;
short dq[N], l, r;
int main(){
	h = R(), w = R(), k = R();
	int cnt = 0;
	FOO(i,1,h){
		FOO(j,1,w){
			char c = RC();
			a[i][j] = (c == '-' ? -1 : (c == '+')) + a[i-1][j];
			cnt += (c == '+');
		}
		RC();
	}
	if(cnt < k){ W(-1); return 0;}
	FOO(u,1,h) FOO(d,u,h){
		FOO(i,1,w) b[i] = b[i-1] + a[d][i] - a[u-1][i];
		l = r = 0, dq[r++] = 0;
		FOO(i,1,w){
			while(l < r and b[dq[r-1]] >= b[i]) --r;
			dq[r++] = i;
			while(l < r and b[i] - b[dq[l]] >= k){
				chmin(ans, (d - u + 1) * (i - dq[l]));
				++l;
			}
		}
		if(ans == k) break;
	}
	W(ans == inf ? -1 : ans);
	return 0;
}
