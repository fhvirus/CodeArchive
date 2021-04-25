#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<iostream>
#include<algorithm>
using namespace std;
#define fi(i,a,b) for(int i=a;i<=b;++i)
#define fd(i,a,b) for(int i=a;i>=b;--i)
#define N 1600
#define NINF -700000000
int m, n, k, s[N][N];
// lu ru ld rd
// - |
int a[N][N], b[N][N], c[N][N], d[N][N];
int u[N], v[N];

signed main(){
	m = R(), n = R(), k = R();

	fi(i,1,m)fi(j,1,n) s[i][j] = R() + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
	fd(i,m,k)fd(j,n,k) s[i][j] = s[i][j] - s[i-k][j] - s[i][j-k] + s[i-k][j-k];

	fi(i,k,m){
		fi(j,k,n) a[i][j] = max({s[i][j], a[i-1][j], a[i][j-1]});
		fd(j,n-k+1,1) b[i][j] = max({s[i][j+k-1], b[i-1][j], b[i][j+1]});
	}
	fd(i,m-k+1,1){
		fi(j,k,n) c[i][j] = max({s[i+k-1][j], c[i+1][j], c[i][j-1]});
		fd(j,n-k+1,1) d[i][j] = max({s[i+k-1][j+k-1], d[i+1][j], d[i][j+1]});
	}

	fi(i,k,m)fi(j,k,n) u[i] = max(u[i], s[i][j]);
	fi(i,k,m)fi(j,k,n) v[j] = max(v[j], s[i][j]);

	int ans = NINF;
	fi(i,k,m-k)fi(j,k,n-k) ans = max({
		ans,
		a[i][j] + b[i][j + 1] + c[i + 1][n],     // _|_
		a[m][j] + b[i][j + 1] + d[i + 1][j + 1], // |-
		a[i][n] + c[i + 1][j] + d[i + 1][j + 1], // "|"
		a[i][j] + b[m][j + 1] + c[i + 1][j]      // -|
	});

	// =
	fi(i,k,m-2*k)fi(j,i+k,m-k) ans = max(ans, a[i][n] + u[j] + c[j+1][n]);
	fi(i,k,n-2*k)fi(j,i+k,n-k) ans = max(ans, a[m][i] + v[j] + b[m][j+1]);

	W(ans);
	return 0;
}