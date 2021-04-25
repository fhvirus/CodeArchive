#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2")
#pragma loot-opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}



const int RANGE = 1e6;
struct bit{
	int val[RANGE + 1];
	inline void add(int p){
		for(; p <= RANGE; p += p & -p) ++val[p];
	}
	inline int query(int p){
		int ans = 0;
		for(; p; p ^= p & -p) ans += val[p];
		return ans;
	}
	inline int search(int v){
		int sum = 0, pos = 0;
		for(int i = 20; i >= 0; --i){
			if(pos + (1<<i) < RANGE and sum + val[pos + (1<<i)] < v)
				sum += val[pos + (1<<i)],
				pos += 1<<i;
		}
		return pos + 1;
	}
} bit;

int q, cmd, x, cnt;
int main(){
	q = R();
	for(; q; --q){
		cmd = R();
		if(cmd == 1)
			bit.add(R()), ++cnt;
		else
			W(bit.search((cnt+1)/2));
	}
	write(1,OB,OP);
}