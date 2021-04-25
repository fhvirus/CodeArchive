#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 1e6;
int n, m;

// check if solution exist
int dsu1[N*2];
inline int find1(int a){ return a == dsu1[a] ? a : dsu1[a] = find1(dsu1[a]);}
inline void union1(int a, int b){ if(find1(a) != find1(b)) dsu1[dsu1[b]] = dsu1[a];}

// count ans
int dsu2[N];
inline int find2(int a){ return a == dsu2[a] ? a : dsu2[a] = find2(dsu2[a]);}
inline void union2(int a, int b){ if(find2(a) != find2(b)) dsu2[dsu2[b]] = dsu2[a];}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i)
		dsu1[i] = dsu2[i] = i, dsu1[i + n] = i + n;
	for(int i = 0, u, v, c; i < m; ++i){
		u = R(), v = R(), c = R();
		union1(u, c == 1 ? v : v + n);
		union1(u + n , c == 1 ? v + n : v);
		union2(u, v);
	}
	bool yas = true;
	for(int i = 0; i < n; ++i)
		if(find1(i) == find1(i + n)){
			yas = false;
			break;
		}
	if(!yas){ W(0); return 0;}

	int ans = 0, root = find2(0);
	for(int i = 0; i < n; ++i)
		if(find2(i) != root) union2(root, i), ans++;
	long long res = 1;
	for(int i = 0; i < ans; ++i)
		res *= 2, res %= 1000000007;
	W(res);
	return 0;
}