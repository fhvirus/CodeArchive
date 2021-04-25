// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';write(1,OB,OP);}

#include<vector>
using namespace std;

struct multiset{
	int n, l;
	vector<int> v;
	multiset(int _n){
		n = _n + 5;
		l = __lg(n);
		v.resize(n, 0);
	}
	inline void modify(int p, int val){ for(; p < n; p += p & -p) v[p] += val;}
	int query(int p){
		int ans = 0;
		for(; p; p -= p & -p) ans += v[p];
		return ans;
	}
	void eraser(int val){
		++val;
		int cnt = query(val);
		if(size() == cnt) return;
		int p = 0, sum = 0;
		for(int i = 1<<l; i; i >>= 1){
			if((p + i) < n and sum + v[p + i] <= cnt)
				sum += v[p += i];
		}
		modify(p + 1, -1);
	}
	int size(){
		return query(n-1);
	}
};

int main(){
	int n = R();
	multiset ms(n);
	for(; n; --n){
		ms.modify(R() + 1, 1);
		ms.eraser(R());
	}
	W(ms.size());
	return 0;
}
