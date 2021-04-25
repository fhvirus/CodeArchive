#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}
#include<algorithm>
#include<unordered_map>
using namespace std;
#define ll long long
const int N = 1e5 + 225;
int t, n;
struct point{
	int x, y;
	bool operator<(const point &rhs) const{
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
} p[N];
struct edge{
	int c, a, b;
	bool operator<(const edge &rhs) const{
		return c < rhs.c;
	}
} e[N<<1];
int ptr;

int dsu[N];
inline int Find(int a){ return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);}
inline void Union(int a, int b){ dsu[dsu[b]] = dsu[a];}

unordered_map<int, int> last;

int main(){
	t = R();
	for(; t; --t){
		n = R();
		last.clear();
		for(int i = 0; i < n; ++i)
			p[i].x = R(), p[i].y = R(), dsu[i] = i;
		std::sort(p, p + n);

		ptr = 0;
		for(int i = 0; i < n; ++i){
			if(i > 0 and p[i].x == p[i-1].x)
				e[ptr++] = {p[i].y - p[i-1].y, i, i-1};
			if(last.count(p[i].y) != 0)
				e[ptr++] = {p[i].x - p[last[p[i].y]].x, i, last[p[i].y]};
			last[p[i].y] = i;
		}
		std::sort(e, e + ptr);

		ll ans = 0;
		for(int i = 0; i < ptr; ++i){
			if(Find(e[i].a) == Find(e[i].b)) continue;
			Union(e[i].a, e[i].b);
			ans += e[i].c;
		}
		W(ans);
	}
	write(1,OB,OP);
}