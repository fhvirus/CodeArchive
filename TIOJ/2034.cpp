// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65535)write(1,OB,OP),OP=0;}
const int N = 101;
int n, mx = 0, mn = 1001, cnt[1001];
int main(){
	n = R();
	for(int i = 0, a; i < n; ++i){
		a = R();
		mx = mx > a ? mx : a;
		mn = mn < a ? mn : a;
		cnt[a]++;
	}
	W(mn), W(mx);
	if(mx - mn >= n){
		OB[OP++] = 'n';
		OB[OP++] = 'o';
	} else {
		OB[OP++] = 'y';
		OB[OP++] = 'e';
		OB[OP++] = 's';
	}
	write(1,OB,OP);
	return 0;
}
