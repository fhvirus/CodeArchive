#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[10000]; int OP;
inline char RC(){static char buf[10000],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,10000))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void puts(bool eek){
	if(eek){
		OB[OP++] = 'Y';
		OB[OP++] = 'e';
		OB[OP++] = 's';
	} else {
		OB[OP++] = 'N';
		OB[OP++] = 'o';
	}
	OB[OP++] = '\n';
}
inline int min(int a, int b){ return a < b ? a : b;}
int n, m, a[100], sum;
bool dp[10001];
int main(){
	m = R(), n = R();
	for(; m; --m){
		sum = 0;
		for(int i = 0; i < n; ++i) sum += (a[i] = R());
		if(sum&1){ puts(false); continue;}
		for(int i = 0; i < 10001; ++i) dp[i] = false;
		dp[0] = true;
		for(int i = 0; i < n; ++i){
			for(int j = min(sum - a[i], 10001 - a[i]); j >= 0; --j)
				if(dp[j]) dp[j + a[i]] = true;
		}
		puts(dp[sum>>1]);
	}
	write(1,OB,OP);
}