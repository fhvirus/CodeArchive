#pragma Os
#define FOR(i,n) for(int i=0;i<n;++i)
#include<unistd.h>
char OB[40], OP;
inline char RC(){static char buf[1024],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,1024))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';}


const int K = 5, N = 50;
int k, n, s, p[N][2 * K + 1], u[N][2 * K + 1], l[N][2 * K + 1];

int main(){
	k = R(), n = R();
	FOR(i, n){
		s = R();
		FOR(j, 2 * k + 1) p[i][j] = R();
		FOR(j, 2 * k + 1) u[i][j] = R();
		FOR(j, 2 * k + 1) l[i][j] = R();
	}
	int jiz, eek;
	for(int i = n-1; i >= 0; --i){
		bool ans = true;
		FOR(j, n){
			if(i == j) continue;
			FOR(d, k + 1)
				if(p[i][d] < p[j][d + k] or (p[i][d] == p[j][d + k] and i > j))
					{ans = false; break;}
		}
		if(ans){ jiz = i + 1; break;}
	}
	for(int i = n-1; i >= 0; --i){
		bool ans = true;
		FOR(j, n){
			if(i == j) continue;
			FOR(d, k + 1)
				if(u[i][d] < l[j][d + k] or (u[i][d] == l[j][d + k] and i > j))
					{ans = false; break;}
		}
		if(ans){ eek = i + 1; break;}
	}
	W(jiz), W(eek), write(1,OB,OP);
}