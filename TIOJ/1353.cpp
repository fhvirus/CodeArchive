#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma loop_opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
#include<algorithm>
using namespace std;

const int N = 1e6 + 1;
struct EEK{
	int val[379720], p;
	inline void push_back(int v){
		val[p++] = v;
	}
	inline int* begin(){
		return val;
	}
	inline int* end(){
		return val + p;
	}
	inline int size(){
		return p;
	}
} eek[8];
char cnt[N];
inline void shai(){
	cnt[1] = 0; eek[0].push_back(1);
	for(int i = 2; i < N; ++i){
		if(cnt[i] == 0)
			for(int j = i; j < N; j += i)
				++cnt[j];
		eek[cnt[i]].push_back(i);
	}
}

int main(){
	shai();
	int a, b;
	// for(int i = 0; i < 8; ++i)
	// 	printf("%d\n", eek[i].size());
	while(a = R(), b = R(), a != 0){
		for(int i = 7; i >= 0; --i){
			int l = lower_bound(eek[i].begin(), eek[i].end(), a) - eek[i].begin();
			int r = lower_bound(eek[i].begin(), eek[i].end(), b) - eek[i].begin();
			if(l == r){
				if(eek[i].val[l] == a){
					W(eek[i].val[l], ' ');
					W(i, '\n');
					break;
				}
			} else {
				W(eek[i].val[l], ' ');
				W(i, '\n');
				break;
			}
		}
	}
	write(1,OB,OP);
}